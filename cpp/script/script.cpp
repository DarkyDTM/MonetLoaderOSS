#include "script.h"
#include "script_manager.h"
#include "sol/sol.hpp"

sol::variadic_results lua::script::exported_function::call(sol::variadic_args args)
{
  static thread_local std::vector<sol::object> converted_objects;
  static thread_local std::unordered_map<const void*, sol::object> table_cache;

  auto ptr = function.lock();
  script* func_s = script_manager::get_script(function_script_id);
  script* this_s = script_manager::get_script(caller_script_id);
  if (ptr && func_s) {
    table_cache.clear();
    converted_objects.clear();
    for (auto i : args) {
      converted_objects.push_back(this_s->exported_copy(func_s->state, func_s->id, i, table_cache));
    }

    sol::protected_function_result pfr = (*ptr)(sol::as_args(converted_objects));
    converted_objects.clear();
    table_cache.clear();
    if (!pfr.valid()) {
      sol::error e = pfr;
      throw sol::error { std::string { "while calling exported function: " } + e.what() };
    }

    sol::variadic_results r;
    for (auto i : pfr) {
      r.push_back(func_s->exported_copy(this_s->state, this_s->id, i, table_cache));
    }
    table_cache.clear();
    return r;
  } else {
    throw sol::error { "tried to invoke exported function of unloaded script" };
  }
}

bool lua::script::lua_info::get_dead()
{
  script* s = script_manager::get_script(id);
  return !s || s->dead;
}

lua::script::script(std::size_t id, std::filesystem::path path)
    : id(id)
    , sched(state)
{
  info.id = id;
  info.path = path;
  info.directory = path.parent_path().filename();
  info.filename = path.filename();
  info.name = info.filename;
  state.open_libraries();
}

lua::script::~script()
{
  for (auto& i : commands) {
    script_manager::_commands.erase(i);
  }
  for (auto i : allocations) {
    std::free(i);
  }
  for (auto& i : imported_map) {
    script* s = script_manager::get_script(i.first);
    if (s) {
      s->exported_function_handles.erase(id);
    }
  }
}

void lua::script::apply_property(const std::string& property)
{
  if (property == "work-in-pause") {
    flags |= script_flags::work_in_pause;
  }
  if (property == "forced-reloading-only") {
    flags |= script_flags::forced_reloading_only;
  }
  info.properties.push_back(property);
}

sol::table lua::script::get_exports(std::size_t copy_script_id)
{
  script* s = script_manager::get_script(copy_script_id);
  auto it = s->imported_map.find(id);
  if (it != s->imported_map.end()) {
    return it->second;
  } else {
    sol::object exports_table = state["EXPORTS"];
    if (!exports_table.valid() || exports_table.get_type() != sol::type::table) {
      exports_table = state.create_table();
    }

    std::unordered_map<const void*, sol::object> table_cache;
    sol::table copy = exported_copy(script_manager::get_script(copy_script_id)->state, copy_script_id, exports_table, table_cache);
    s->imported_map[id] = copy;
    return copy;
  }
}

sol::object lua::script::exported_copy(sol::state& copy_state, std::size_t copy_script_id, sol::object obj, std::unordered_map<const void*, sol::object>& table_cache)
{
  sol::type type = obj.get_type();

  switch (type) {
  case sol::type::userdata:
  case sol::type::thread:
    throw sol::error { "cannot export userdata or thread" };

  case sol::type::none:
  case sol::type::lua_nil:
    return sol::make_object(copy_state, sol::lua_nil);

  case sol::type::number:
    return sol::make_object(copy_state, obj.as<double>());
  case sol::type::string:
    return sol::make_object(copy_state, obj.as<std::string>());
  case sol::type::boolean:
    return sol::make_object(copy_state, obj.as<bool>());
  case sol::type::lightuserdata:
    return sol::make_object(copy_state, sol::lightuserdata_value { obj.as<void*>() });

  case sol::type::function: {
    sol::protected_function pfn = obj;
    auto shared = std::make_shared<sol::protected_function>(pfn);
    exported_function_handles.emplace(copy_script_id, shared);

    exported_function ef { id, copy_script_id, shared };
    return sol::make_object(copy_state, [ef](sol::variadic_args args) mutable {
      return ef.call(args);
    });
  }

  case sol::type::table: {
    auto it = table_cache.find(obj.pointer());
    if (it != table_cache.end()) {
      return it->second;
    }

    sol::table as_t = obj.as<sol::table>();
    sol::table t = copy_state.create_table(0, static_cast<int>(as_t.size()));
    table_cache.emplace(obj.pointer(), t);
    for (auto& [k, v] : as_t) {
      t.set(exported_copy(copy_state, copy_script_id, k, table_cache), exported_copy(copy_state, copy_script_id, v, table_cache));
    }
    return t;
  }
  case sol::type::poly:
    break;
  }

  return sol::make_object(copy_state, sol::lua_nil);
}
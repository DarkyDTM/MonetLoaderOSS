#pragma once
#include "scheduler.h"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lua {
namespace script_flags {
  enum {
    work_in_pause = (1 << 0),
    forced_reloading_only = (1 << 1),
  };
}

struct script {
  class exported_function {
public:
    exported_function(std::size_t function_script_id, std::size_t caller_script_id, std::weak_ptr<sol::protected_function> function)
    {
      this->function_script_id = function_script_id;
      this->caller_script_id = caller_script_id;
      this->function = function;
    }

    sol::variadic_results call(sol::variadic_args args);

private:
    std::size_t function_script_id;
    std::size_t caller_script_id;
    std::weak_ptr<sol::protected_function> function;
  };

  struct lua_info {
    std::size_t id; // duplicated for Lua
    std::string path;
    std::string directory;
    std::string filename;
    std::string name;
    std::vector<std::string> authors;
    std::string description;
    std::string version;
    int version_number;
    std::string url;
    std::vector<std::string> dependencies;
    std::vector<std::string> properties;

    bool get_dead();

    bool operator==(const lua_info& rhs) const
    {
      return id == rhs.id;
    }
  };

  script(std::size_t id, std::filesystem::path path);
  ~script();

  void apply_property(const std::string& property);

  sol::table get_exports(std::size_t copy_script_id);
  sol::object exported_copy(sol::state& copy_state, std::size_t copy_script_id, sol::object obj,
      std::unordered_map<const void*, sol::object>& table_cache);

  std::size_t id; // id of script, unique for entire lifetime of script manager
  sol::state state {}; // main lua state
  scheduler sched; // scheduler of this script, used for main and lua_thread
  std::size_t main_thread_id { 0 }; // id of thread that executes main() function, used to prevent starting it repeatedly
  std::uint32_t flags {}; // see script_flags
  bool dead {}; // the script is no longer active (due to error or smth else), but it's instance has not been unloaded yet
  // if set to true, the script is going to die immediately and so all errors from event handlers are suppressed
  bool dying {};
  lua_info info {}; // info about script from lua functions, exported using script api
  // map of event handlers by name
  std::unordered_map<std::string, std::vector<sol::protected_function>> event_handlers {};
  std::unordered_set<std::string> commands {}; // names of registered commands (used to unregister them on unload)
  std::unordered_set<void*> allocations {}; // active allocations, freed automatically on unload

  // map of (script id) -> (exported function shared ptrs), used to invalidate exported function weak ptr
  // on unload
  std::unordered_multimap<std::size_t, std::shared_ptr<sol::protected_function>> exported_function_handles {};
  // cache of other scripts exports
  std::unordered_map<std::size_t, sol::table> imported_map {};

  // Search stuff
  int last_ped {};
  int last_vehicle {};
  int last_object {};
};
}
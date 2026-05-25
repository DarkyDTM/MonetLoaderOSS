#include "luajson.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <spdlog/spdlog.h>
#include <string_view>

namespace {
template <typename Allocator>
rapidjson::Value make_string(Allocator& alloc, std::string_view sv)
{
  return rapidjson::Value { sv.data(), static_cast<rapidjson::SizeType>(sv.length()), alloc };
}

template <typename Allocator>
std::optional<rapidjson::Value> as_array(Allocator& alloc, sol::table t, const std::string& debug_name);
template <typename Allocator>
std::optional<rapidjson::Value> as_dict(Allocator& alloc, sol::table t, const std::string& debug_name);

template <typename Allocator>
std::optional<rapidjson::Value> encode_value(Allocator& alloc, sol::object o, const std::string& debug_name)
{
  auto type = o.get_type();

  switch (type) {
  case sol::type::boolean: {
    return rapidjson::Value { o.as<bool>() };
  }
  case sol::type::number: {
    if (o.is<int>() && o.as<int>() == o.as<double>()) {
      return rapidjson::Value { o.as<int>() };
    }
    return rapidjson::Value { o.as<double>() };
  }
  case sol::type::string: {
    return std::move(make_string(alloc, o.as<std::string_view>()));
  }
  case sol::type::lua_nil: {
    return rapidjson::Value { rapidjson::kNullType };
  }
  case sol::type::table: {
    auto t = o.as<sol::table>();
    std::optional<rapidjson::Value> opt = std::move(as_array(alloc, t, debug_name));
    if (opt.has_value()) {
      return std::move(*opt);
    }
    return std::move(as_dict(alloc, t, debug_name));
  }
  case sol::type::lightuserdata: {
    if (o.as<sol::lightuserdata>().pointer() == nullptr) {
      return rapidjson::Value { rapidjson::kNullType };
    }
    [[fallthrough]];
  }
  default: {
    throw std::runtime_error(fmt::format("json: cannot encode value of key '{}': not a boolean/number/string/table/null", debug_name));
    return std::nullopt;
  }
  }
}

template <typename Allocator>
std::optional<rapidjson::Value> as_array(Allocator& alloc, sol::table t, const std::string& debug_name)
{
  std::size_t size = t.size();
  if (size == 0 || !t[1].valid()) {
    return std::nullopt; // Most of cases
  }

  rapidjson::Value v {};
  v.SetArray();
  v.Reserve(size, alloc);
  for (std::size_t i = 1; i <= size; ++i) {
    auto el = t[i];
    if (!el.valid()) {
      return std::nullopt; // Sparse array
    }

    std::optional<rapidjson::Value> o = std::move(encode_value(alloc, el, debug_name));
    if (o.has_value()) {
      v.PushBack(std::move(*o), alloc);
    } else {
      v.PushBack(rapidjson::Value { rapidjson::kNullType }, alloc);
    }
  }

  return v;
}

template <typename Allocator>
std::optional<rapidjson::Value> as_dict(Allocator& alloc, sol::table t, const std::string& debug_name)
{
  rapidjson::Value v {};
  v.SetObject();
  v.MemberReserve(t.size(), alloc);
  for (auto& i : t) {
    std::string k;
    auto first_t = i.first.get_type();
    if (first_t == sol::type::string) {
      k = i.first.as<std::string_view>();
    } else if (first_t == sol::type::number) {
      auto n = i.first.as<double>();
      auto rounded = std::llround(n);
      if (n == static_cast<double>(rounded)) {
        k = std::to_string(rounded);
      } else {
        k = std::to_string(n);
      }
    } else {
      throw std::runtime_error(fmt::format("json: cannot encode key of table '{}': not a string or number", debug_name));
      continue;
    }

    std::optional<rapidjson::Value> encoded = std::move(encode_value(alloc, i.second, debug_name + "." + k));
    if (!encoded.has_value()) {
      continue;
    }

    v.AddMember(make_string(alloc, k).Move(), encoded->Move(), alloc);
  }

  return v;
}

sol::object decode_value(sol::state_view state, rapidjson::Value& v)
{
  switch (v.GetType()) {
  case rapidjson::kNullType: {
    return sol::nil;
  }
  case rapidjson::kFalseType: {
    return sol::make_object(state, false);
  }
  case rapidjson::kTrueType: {
    return sol::make_object(state, true);
  }
  case rapidjson::kNumberType: {
    if (v.IsInt()) {
      return sol::make_object(state, v.GetInt());
    }
    return sol::make_object(state, v.GetDouble());
  }
  case rapidjson::kStringType: {
    return sol::make_object(state, std::string_view { v.GetString(), v.GetStringLength() });
  }
  case rapidjson::kArrayType: {
    std::size_t size = v.Size();
    sol::table table { state, sol::new_table { static_cast<int>(size) } };
    for (std::size_t i = 0; i < size; ++i) {
      table[i + 1] = decode_value(state, v[i]);
    }
    return table;
  }
  case rapidjson::kObjectType: {
    sol::table table { state, sol::new_table { 0, static_cast<int>(v.MemberCount()) } };
    for (auto it = v.MemberBegin(); it != v.MemberEnd(); ++it) {
      char* endptr;
      const char* str = it->name.GetString();
      double d = std::strtod(str, &endptr);
      if (endptr != str) {
        table[d] = decode_value(state, it->value);
      } else {
        table[decode_value(state, it->name)] = decode_value(state, it->value);
      }
    }
    return table;
  }
  }
}
}

std::string luajson::encode(sol::table table, bool compact)
{
  rapidjson::Document doc {};
  auto encoded = encode_value(doc.GetAllocator(), table, "<root>");
  if (!encoded.has_value()) {
#ifdef __GNUC__
    __builtin_unreachable();
#elif defined(_MSC_VER)
    __assume(false);
#endif
    return "";
  }
  rapidjson::Value v { std::move(*encoded) };

  if (compact) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    v.Accept(writer);
    return std::string { buffer.GetString(), buffer.GetSize() };
  } else {
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    v.Accept(writer);
    return std::string { buffer.GetString(), buffer.GetSize() };
  }
}

sol::table luajson::decode(sol::state_view state, std::string_view json)
{
  rapidjson::Document doc {};
  rapidjson::ParseResult result = doc.Parse(json.data(), json.length());
  if (result.IsError()) {
    throw std::runtime_error(fmt::format("json parse: {} (at: {})", rapidjson::GetParseError_En(result.Code()), result.Offset()));
    return sol::nil;
  }

  return decode_value(state, doc);
}
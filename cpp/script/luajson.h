#pragma once
#include <sol/sol.hpp>
#include <string_view>

namespace luajson {
std::string encode(sol::table table, bool compact = false);
sol::table decode(sol::state_view state, std::string_view json);

struct null_t { };
}
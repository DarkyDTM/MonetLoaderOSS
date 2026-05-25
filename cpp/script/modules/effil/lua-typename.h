#pragma once
#include "sol/sol.hpp"
#include "shared-table.h"
#include "channel.h"
#include "thread.h"

namespace effil {
template <typename SolObject>
std::string luaTypename(const SolObject& obj)
{
  if (obj.get_type() == sol::type::userdata) {
    if (obj.template is<SharedTable>())
      return "effil.table";
    else if (obj.template is<Channel>())
      return "effil.channel";
    else if (obj.template is<Thread>())
      return "effil.thread";
    else
      return "userdata";
  } else {
    return lua_typename(obj.lua_state(), (int)obj.get_type());
  }
}
}
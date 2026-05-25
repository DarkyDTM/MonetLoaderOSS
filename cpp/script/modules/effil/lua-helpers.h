#pragma once

#include "sol/sol.hpp"
#include "stored-object.h"
#include "utils.h"

namespace effil {

class SharedTable;
class Channel;
class Thread;

std::string dumpFunction(const sol::function& f);
sol::function loadString(const sol::state_view& lua, const std::string& str,
    const sol::optional<std::string>& source = sol::nullopt);
std::chrono::milliseconds fromLuaTime(int duration, const sol::optional<std::string>& period);

typedef std::vector<effil::StoredObject> StoredArray;

class Timer {
  public:
  Timer(const std::chrono::milliseconds& timeout);
  bool isFinished();
  std::chrono::milliseconds left();

  private:
  std::chrono::milliseconds timeout_;
  std::chrono::high_resolution_clock::time_point startTime_;
};

} // namespace effil

inline int sol_lua_push(lua_State* state, const effil::StoredArray& args)
{
  int p = 0;
  for (const auto& i : args) {
    p += sol::stack::push(state, i->unpack(sol::this_state { state }));
  }
  return p;
}

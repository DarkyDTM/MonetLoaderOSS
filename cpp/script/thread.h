#pragma once
#include "script.h"
#include <cstddef>
#include <string>

namespace lua {
class thread {
  public:
  thread(script& s, sol::protected_function func)
      : _s(s)
      , _func(sol::protected_function { s.state, func })
      , _work_in_pause(s.flags & script_flags::work_in_pause)
  {
  }

  static thread create_suspended(script& s, sol::protected_function func);
  static thread create(script& s, sol::protected_function func, sol::variadic_args args);

  void run(sol::variadic_args args);
  std::string status();
  void terminate();

  void set_work_in_pause(bool toggle);
  bool get_work_in_pause();
  bool get_dead();

  private:
  script& _s;
  sol::protected_function _func;
  std::size_t _thread_id { 0 };
  bool _work_in_pause;
};
}
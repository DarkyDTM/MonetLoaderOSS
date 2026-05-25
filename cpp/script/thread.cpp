#include "thread.h"
#include <spdlog/spdlog.h>

lua::thread lua::thread::create_suspended(script& s, sol::protected_function func)
{
  thread thr { s, func };
  return thr;
}

lua::thread lua::thread::create(script& s, sol::protected_function func, sol::variadic_args args)
{
  thread thr { s, func };
  thr.run(args);
  return thr;
}

void lua::thread::run(sol::variadic_args args)
{
  if (_thread_id == 0 || get_dead()) {
    auto v = _s.sched.start(_func, _work_in_pause, args);
    if (std::holds_alternative<sol::error>(v)) {
      auto e = std::get<sol::error>(v);
      throw e;
    } else {
      _thread_id = std::get<std::size_t>(v);
    }
  }
}

std::string lua::thread::status()
{
  if (_thread_id == 0) {
    return "suspended";
  }

  sol::thread_status st = _s.sched.thread_status(_thread_id);
  if (st == sol::thread_status::ok) {
    return "running";
  }
  if (st == sol::thread_status::yielded) {
    return "yielded";
  }
  if (st == sol::thread_status::dead) {
    return "dead";
  }

  return "error";
}

void lua::thread::terminate()
{
  _s.sched.terminate(_thread_id);
}

void lua::thread::set_work_in_pause(bool toggle)
{
  _work_in_pause = toggle;
  _s.sched.set_work_in_pause(_thread_id, toggle);
}

bool lua::thread::get_work_in_pause()
{
  return _work_in_pause;
}

bool lua::thread::get_dead()
{
  return status() == "dead";
}
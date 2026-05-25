#pragma once
#include <deque>
#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <utility>

namespace lua {
// a base class for scheduler tasks
class scheduler_task {
  public:
  virtual ~scheduler_task() = default;
  virtual bool is_complete() = 0;
};

// callback_task is a convenience scheduler task
// that allows user to bind functions, function objects,
// lambdas, etc. as tasks to the scheduler
class callback_task : public scheduler_task {
  public:
  callback_task(std::function<bool()> callback)
      : _callback(std::move(callback))
  {
  }

  bool is_complete() override
  {
    return _callback();
  }

  private:
  std::function<bool()> _callback;
};

namespace detail {
  struct scheduler_cothread {
    sol::thread thread;
    sol::coroutine coroutine;
    std::size_t thread_id;
    bool work_in_pause;

    scheduler_cothread(sol::state& state, std::size_t thread_id, bool work_in_pause, sol::protected_function func)
        : thread_id(thread_id)
        , work_in_pause(work_in_pause)
    {
      thread = sol::thread::create(state);
      coroutine = sol::coroutine { thread.state(), func };
    }
  };

  struct scheduler_thread_task {
    std::shared_ptr<scheduler_cothread> thread;
    std::unique_ptr<scheduler_task> task;
  };
}

class scheduler {
  public:
  scheduler(sol::state& state)
      : _state(state)
  {
  }

  std::variant<std::size_t, sol::error> start(sol::protected_function func, bool work_in_pause, std::optional<sol::variadic_args> args = std::nullopt)
  {
    // create the thread
    std::size_t thread_id = _next_thread_id++;
    _thread_stack.push_back(std::make_shared<detail::scheduler_cothread>(_state, thread_id, work_in_pause, func));

    // start the thread
    sol::protected_function_result pfr;
    if (!args.has_value()) {
      pfr = _thread_stack.back()->coroutine();
    } else {
      pfr = _thread_stack.back()->coroutine(args.value());
    }

    // handle possible errors
    if (!pfr.valid()) {
      sol::error e = pfr;
      _thread_stack.pop_back();
      return e;
    }

    _thread_stack.pop_back();
    return thread_id;
  }

  std::optional<sol::error> run(bool in_pause);
  void yield(std::unique_ptr<scheduler_task> task);

  // for lua_thread

  void terminate(std::size_t thread_id)
  {
    _tasks.erase(thread_id);
  }

  sol::thread_status thread_status(std::size_t thread_id)
  {
    auto i = _tasks.find(thread_id);
    if (i == _tasks.end()) {
      for (auto& j : _thread_stack) {
        if (j->thread_id == thread_id) {
          return j->thread.status();
        }
      }
      return sol::thread_status::dead;
    }
    return i->second.thread->thread.status();
  }

  void set_work_in_pause(std::size_t thread_id, bool work_in_pause)
  {
    auto i = _tasks.find(thread_id);
    if (i == _tasks.end()) {
      for (auto& j : _thread_stack) {
        if (j->thread_id == thread_id) {
          j->work_in_pause = work_in_pause;
          break;
        }
      }
      return;
    }
    i->second.thread->work_in_pause = work_in_pause;
  }

  // misc accessors

  std::size_t current_thread_id()
  {
    if (_thread_stack.size() == 0) {
      return 0;
    }
    return _thread_stack.back()->thread_id;
  }

  std::size_t pending_tasks()
  {
    return _tasks.size();
  }

  // yields a thread; copies the passed scheduler_task
  template <typename T, typename std::enable_if_t<std::is_base_of_v<scheduler_task, T>>* = nullptr>
  void yield(const T& task)
  {
    yield(std::make_unique<T>(task));
  }

  template <typename T, typename... Args, typename std::enable_if_t<std::is_base_of_v<scheduler_task, T>>* = nullptr>
  void yield(Args... args)
  {
    yield(std::make_unique<T>(args...));
  }

  // we also want to support plain function types as tasks
  void yield(bool (*callback)())
  {
    yield(std::make_unique<callback_task>(callback));
  }

  // // a convenience function for registering a yielding, optionally stateful, C++ function
  // template <typename F>
  // void register_function(std::string name, F&& f)
  // {
  // 	_state[name] = sol::yielding(std::forward<F>(f));
  // }

  private:
  sol::state& _state;
  std::size_t _next_thread_id { 1 };
  std::map<std::size_t, detail::scheduler_thread_task> _tasks {};
  std::deque<std::shared_ptr<detail::scheduler_cothread>> _thread_stack {};
};
}
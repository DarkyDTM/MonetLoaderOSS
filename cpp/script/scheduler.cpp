#include "scheduler.h"

std::optional<sol::error> lua::scheduler::run(bool in_pause)
{
  // iterate through all pending tasks
  for (auto i = _tasks.begin(); i != _tasks.end();) {
    // if the thread is dead, remove it
    if (i->second.thread->coroutine.status() != sol::call_status::yielded) {
      i = _tasks.erase(i);
      continue;
    }

    // is this task complete?
    if (i->second.task->is_complete() && (!in_pause || i->second.thread->work_in_pause)) {
      // set the current thread
      _thread_stack.push_back(i->second.thread);
      // remove it from the pending list
      i = _tasks.erase(i);
      // resume the thread
      auto pfr = _thread_stack.back()->coroutine();

      // handle possible errors
      if (!pfr.valid()) {
        sol::error e = pfr;
        _thread_stack.pop_back();
        return e;
      }

      _thread_stack.pop_back();
    } else {
      ++i;
    }
  }

  return std::nullopt;
}

void lua::scheduler::yield(std::unique_ptr<scheduler_task> task)
{
  // store task
  detail::scheduler_thread_task thread_task;
  thread_task.thread = _thread_stack.back();
  thread_task.task = std::move(task);
  _tasks.emplace(thread_task.thread->thread_id, std::move(thread_task));
}
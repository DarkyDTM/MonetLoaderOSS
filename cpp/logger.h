#pragma once
#include "script/script.h"
#include <spdlog/spdlog.h>


namespace logger {
inline std::filesystem::path absolute_path;
inline std::filesystem::path relative_path;

enum levels {
  LV_DEBUG = 2,
  LV_ERROR = 3,
  LV_WARN = 4,
  LV_SYSTEM = 5
};
void init();

void invoke_message_callbacks(int level, lua::script* script, const std::string& msg);
void invoke_script_message_callbacks(lua::script& script, const std::string& msg);

template <int Level, bool Callbacks = true, typename... Args>
void log(lua::script* script, fmt::format_string<Args...> fmt, Args&&... args)
{
  std::string msg = fmt::format(fmt, std::forward<Args>(args)...);

  if constexpr (Level == LV_SYSTEM) {
    if (script) {
      spdlog::info("{}: {}", script->info.name, msg);
    } else {
      spdlog::info("{}", msg);
    }
  } else if constexpr (Level == LV_DEBUG) {
    if (script) {
      spdlog::debug("{}: {}", script->info.name, msg);
    } else {
      spdlog::debug("{}", msg);
    }
  } else if constexpr (Level == LV_ERROR) {
    if (script) {
      spdlog::error("{}: {}", script->info.name, msg);
    } else {
      spdlog::error("{}", msg);
    }
  } else if constexpr (Level == LV_WARN) {
    if (script) {
      spdlog::warn("{}: {}", script->info.name, msg);
    } else {
      spdlog::warn("{}", msg);
    }
  }

  if constexpr (Callbacks) {
    invoke_message_callbacks(Level, script, msg);
  }
}

template <bool Callbacks = true, typename... Args>
void script_log(lua::script& script, fmt::format_string<Args...> fmt, Args&&... args)
{
  std::string msg = fmt::format(fmt, std::forward<Args>(args)...);

  spdlog::trace("{}: {}", script.info.name, msg);

  if constexpr (Callbacks) {
    invoke_script_message_callbacks(script, msg);
  }
}

}
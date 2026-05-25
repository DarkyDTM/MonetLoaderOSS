#include "logger.h"
#include "file_manager.h"
#include "script/script_manager.h"
#include <filesystem>
#include <spdlog/common.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

namespace {
class custom_level_formatter : public spdlog::custom_flag_formatter {
  public:
  void format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) override
  {
    dest.append(std::string_view { "(" });
    if (msg.level == spdlog::level::level_enum::info) {
      dest.append(std::string_view { "system" });
    } else if (msg.level == spdlog::level::level_enum::trace) {
      dest.append(std::string_view { "script" });
    } else {
      dest.append(spdlog::level::to_string_view(msg.level));
    }
    dest.append(std::string_view { ")" });
  }

  [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override
  {
    return spdlog::details::make_unique<custom_level_formatter>();
  }
};
}

void logger::init()
{
  if (!std::filesystem::exists(file_manager::public_external_storage)) {
    return;
  }

  auto rel_file_path = std::filesystem::path{ "monetloader" } / "logs" / "monetloader.log";
  auto file_path = file_manager::public_external_storage / rel_file_path;
  relative_path = rel_file_path.parent_path();
  absolute_path = file_path.parent_path();
  std::filesystem::create_directories(absolute_path);

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path, true);
  file_sink->set_level(spdlog::level::trace);

  auto logger = std::make_shared<spdlog::logger>("monetloader", spdlog::sinks_init_list { file_sink });
  logger->set_level(spdlog::level::trace);
  logger->flush_on(spdlog::level::trace);

  auto formatter = std::make_unique<spdlog::pattern_formatter>();
  formatter->add_flag<custom_level_formatter>('*').set_pattern("[%T.%f] %* %v");
  logger->set_formatter(std::move(formatter));

  spdlog::set_default_logger(logger);
}

void logger::invoke_message_callbacks(int level, lua::script* script, const std::string& msg)
{
  lua::script_manager::for_each_event_handler("onSystemMessage", [level, script, &msg](sol::protected_function fn) -> std::optional<sol::error> {
    auto pfr = script == nullptr ? fn(msg, level, sol::lua_nil) : fn(msg, level, script->info);
    if (!pfr.valid()) {
      sol::error e = pfr;
      return e;
    }
    return std::nullopt;
  });
}

void logger::invoke_script_message_callbacks(lua::script& script, const std::string& msg)
{
  lua::script_manager::for_each_event_handler("onScriptMessage", [&script, &msg](sol::protected_function fn) -> std::optional<sol::error> {
    auto pfr = fn(msg, script.info);
    if (!pfr.valid()) {
      sol::error e = pfr;
      return e;
    }
    return std::nullopt;
  });
}
#pragma once
#include "core/format.h"
#include "stdio.h"
#include <type_traits>
#include <utility>
enum LogLevel { INFO, DEBUG, WARN, ERROR, FATAL, END };

class Logger {
public:
  LogLevel current_level() { return LogLevel::INFO; };

  template <typename... Args>
  using format_string = std::type_identity_t<FormatString<Args...>>;

  // NOTE:NEED TO MARK IT SO IT ONLY ACCECPTS LITERALS
  template <typename... Args>
  void info(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::INFO, fmt.str, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::DEBUG, fmt.str, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warn(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::WARN, fmt.str, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::ERROR, fmt.str, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void inline fatal(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::FATAL, fmt.str, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void log_output(LogLevel level, const char *fmt, Args &&...args) {
    if (level < current_level()) {
      return;
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
    printf(fmt, std::forward<Args>(args)...);
#pragma clang diagnostic pop
  };
};

extern Logger logger;

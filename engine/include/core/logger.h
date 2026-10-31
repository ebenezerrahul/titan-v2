#include "core/format.h"
#include "stdio.h"
#include <type_traits>
enum LogLevel { INFO, DEBUG, WARN, ERROR, FATAL, END };

class Logger {
public:
  LogLevel current_level() { return LogLevel::INFO; };

  template <typename... Args>
  using format_string = std::type_identity_t<FormatString<Args...>>;

  template <typename... Args>
  void info(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::INFO, fmt, args...);
  }

  template <typename... Args>
  void debug(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::DEBUG, fmt, args...);
  }

  template <typename... Args>
  void warn(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::WARN, fmt, args...);
  }

  template <typename... Args>
  void error(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::ERROR, fmt, args...);
  }

  template <typename... Args>
  void inline fatal(format_string<Args...> fmt, Args... args) {
    log_output(LogLevel::FATAL, fmt, args...);
  }

  template <typename... Args>
  void log_output(LogLevel level, format_string<Args...> fmt, Args &&...args) {
    if (level < current_level()) {
      return;
    }
    printf(fmt.str, args...);
  };
};

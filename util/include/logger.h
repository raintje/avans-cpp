#ifndef UTIL_INCLUDE_LOGGER_H
#define UTIL_INCLUDE_LOGGER_H

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

namespace util {

class Logger {
 public:
  explicit Logger();
  ~Logger();

  void WriteLine(const std::string& line);

 private:
  std::ofstream file_;
};

} // namespace util

#endif //UTIL_INCLUDE_LOGGER_H

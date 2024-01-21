#include "logger.h"

namespace util {

Logger::Logger() {
  if (!std::filesystem::is_directory("logs"))
    std::filesystem::create_directory("logs");

  auto t =
      std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()).time_since_epoch().count();
  file_.open("logs/zwaard_en_paard-" + std::to_string(t) + ".txt");
}

Logger::~Logger() { file_.close(); }

void Logger::WriteLine(const std::string &line) {
  mutex_.lock();
  file_ << line << std::endl;
  mutex_.unlock();
}

} // namespace util


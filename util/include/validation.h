#ifndef UTIL_INCLUDE_VALIDATION_H
#define UTIL_INCLUDE_VALIDATION_H

#include <string>
#include <algorithm>

namespace util {

class Validation {
 public:
  ~Validation();
  [[nodiscard]]static bool StringIsNumber(const std::string &s);
 private:
  Validation();
};

} // namespace util

#endif //UTIL_INCLUDE_VALIDATION_H

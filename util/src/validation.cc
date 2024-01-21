#include "validation.h"

namespace util {

Validation::~Validation() = default;
Validation::Validation() =default;

bool Validation::StringIsNumber(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

} // util
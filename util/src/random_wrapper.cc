#include "../include/random_wrapper.h"

namespace util {
RandomWrapper *RandomWrapper::GetInstance() {
  static RandomWrapper instance;
  return &instance;
}

int RandomWrapper::RandomIntInRange(const int min, const int max) {
  std::uniform_int_distribution<int> dist{min, max};
  return dist(engine_);
}

RandomWrapper::~RandomWrapper() = default;
} // namespace util
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

template<typename T>
T RandomWrapper::RandomItemFromVector(const std::vector<T> &vec) {
  if (vec.empty())
    throw std::invalid_argument("[RandomItemFromVector]: Empty vector passed.");

  std::uniform_int_distribution<size_t> dist{0, vec.size() - 1};
  return vec[dist(engine_)];
}

RandomWrapper::~RandomWrapper() = default;
} // namespace util
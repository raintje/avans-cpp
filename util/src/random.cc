#include "../include/random.h"

namespace util {
Random *Random::GetInstance() {
  static Random instance;
  return &instance;
}

int Random::RandomIntInRange(const int min, const int max) {
  std::uniform_int_distribution<int> dist{min, max};
  return dist(engine_);
}

template<typename T>
T Random::RandomItemFromVector(const std::vector<T> &vec) {
  if (vec.empty())
    throw std::invalid_argument("[RandomItemFromVector]: Empty vector passed.");

  std::uniform_int_distribution<size_t> dist{0, vec.size() - 1};
  return vec[dist(engine_)];
}

Random::~Random() = default;
} // namespace util
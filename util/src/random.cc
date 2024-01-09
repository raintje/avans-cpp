#include "../include/random.h"

namespace util {
Random &Random::GetInstance() {
  static Random instance;
  return instance;
}

int Random::RandomIntInRange(int a, int b) {
  std::uniform_int_distribution<int> dist{a, b};
  return dist(engine_);
}

bool Random::PercentChance(double percent = 0.5) {
  std::uniform_real_distribution<double> dist{0, 1};
  return dist(engine_) < percent;
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
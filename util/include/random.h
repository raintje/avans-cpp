#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include <random>
#include <vector>
#include <stdexcept>

namespace util {
class Random {
 public:
  Random(const Random &) = delete;
  Random(Random &&) = delete;
  Random &operator=(const Random &) = delete;
  Random &operator=(Random &&) = delete;

  static Random &GetInstance();

  int RandomIntInRange(int a, int b);
  bool PercentChance(double percent);
  template<typename T>
  T RandomItemFromVector(const std::vector<T> &vec);

  ~Random();
 private:
  std::default_random_engine engine_;
  Random() : engine_(std::random_device{}()) {}
};
} // namespace util

#endif //UTIL_RANDOM_H

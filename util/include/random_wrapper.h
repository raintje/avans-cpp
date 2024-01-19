#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include <random>
#include <vector>
#include <stdexcept>

namespace util {
class RandomWrapper {
 public:
  /// @brief Prohibit copy and move (singleton).
  RandomWrapper(const RandomWrapper &) = delete;
  RandomWrapper(RandomWrapper &&) = delete;
  RandomWrapper &operator=(const RandomWrapper &) = delete;
  RandomWrapper &operator=(RandomWrapper &&) = delete;

  /// @brief Returns the singleton instance of the RandomEngine wrapper.
  static RandomWrapper *GetInstance();

  /// @brief Generates a random integer between the two given integers.
  ///
  /// @param min The floor.
  /// @param max The ceiling.
  ///
  /// @returns A randomly generated integer between min and max.
  int RandomIntInRange(int min, int max);

  /// @brief Generates an integer between 0-100 and returns whether it's bigger or smaller than the given number.
  ///
  /// @param chance The percentage chance, from 0-100.
  /// @returns Whether or not the percent chance was hit.
  bool PercentChance(int chance);

  /// @brief Returns a random item from the given vector.
  ///
  /// @tparam T The type of the elements contained in the vector.
  /// @param vec The vector in question.
  ///
  /// @return A random element from the given vector.
  template<typename T>
  T RandomItemFromVector(const std::vector<T> &vec) {
    if (vec.empty())
      throw std::invalid_argument("[RandomItemFromVector]: Empty vector passed.");

    std::uniform_int_distribution<size_t> dist{0, vec.size() - 1};
    return vec[dist(engine_)];
  };

  /// @brief Default deconstructor.
  ~RandomWrapper();
 private:
  std::default_random_engine engine_;
  RandomWrapper() : engine_(std::random_device{}()) {}
};
} // namespace util

#endif //UTIL_RANDOM_H

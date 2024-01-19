#ifndef DOMAIN_INCLUDE_MODELS_PLAYER_H
#define DOMAIN_INCLUDE_MODELS_PLAYER_H

constexpr int STARTING_GOLD = 100;
constexpr int STARTING_PROVISIONS = 10;

#include <map>

namespace domain::models {
class Player {
 public:
  explicit Player(std::pair<int, int> location);
  ~Player();

  [[nodiscard]]int GetGold() const;
  [[nodiscard]]int GetProvisions() const;

 private:
  std::map<int, int> warband_;
  std::pair<int, int> location_;
  int gold_;
  int provisions_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_PLAYER_H

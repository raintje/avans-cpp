#ifndef DOMAIN_INCLUDE_MODELS_PLAYER_H
#define DOMAIN_INCLUDE_MODELS_PLAYER_H

#include <unordered_map>

namespace domain::models {
class Player {
 public:

  [[nodiscard]]int GetGold() const;
  [[nodiscard]]int GetProvisions() const;

 private:
  std::unordered_map<int, int> warband_;
  int gold;
  int provisions;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_PLAYER_H

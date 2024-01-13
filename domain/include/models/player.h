#ifndef DOMAIN_INCLUDE_MODELS_PLAYER_H
#define DOMAIN_INCLUDE_MODELS_PLAYER_H

constexpr int STARTING_GOLD = 100;
constexpr int STARTING_PROVISIONS = 10;

#include <unordered_map>

#include "tile.h"

namespace domain::models {
class Player : public Tile {
 public:
  explicit Player(structs::Location location);
  ~Player();

  [[nodiscard]]int GetGold() const;
  [[nodiscard]]int GetProvisions() const;
  [[nodiscard]]char GetDrawChar() const override;

 private:
  std::unordered_map<int, int> warband_;
  int gold_;
  int provisions_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_PLAYER_H

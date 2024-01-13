#ifndef DOMAIN_INCLUDE_MODELS_ENEMY_H
#define DOMAIN_INCLUDE_MODELS_ENEMY_H

constexpr int INITIAL_GOLD_MIN = 10;
constexpr int INITIAL_GOLD_MAX = 20;
constexpr int INITIAL_PROVISIONS_MAX = 5;

#include <vector>
#include <string>
#include <unordered_map>

#include "tile.h"

namespace domain::models {

class Enemy : public Tile {
  Enemy(structs::Location location, std::string faction, int threat_level);

  [[nodiscard]]char GetDrawChar() const override;

 private:
  const std::string faction_;
  std::unordered_map<int, int> troops_;
  const int gold_;
  const int provisions_;
};

} // namespace domain::models

#endif // DOMAIN_INCLUDE_MODELS_ENEMY_H

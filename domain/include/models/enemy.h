#ifndef DOMAIN_INCLUDE_MODELS_ENEMY_H
#define DOMAIN_INCLUDE_MODELS_ENEMY_H

#include <vector>
#include <string>
#include <unordered_map>

#include "tile.h"

namespace domain::models {

class Enemy : public Tile {
  Enemy(structs::Location location, const std::string &faction, int troop_count);

  [[nodiscard]]structs::Location GetLocation() const override;
  [[nodiscard]]char GetDrawChar() const override;

 private:
  structs::Location location_;
  std::string faction_;
  std::unordered_map<int, int> troops_;
  int gold_;
  int provisions_;
};

} // namespace domain::models

#endif // DOMAIN_INCLUDE_MODELS_ENEMY_H

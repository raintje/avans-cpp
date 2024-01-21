#ifndef DOMAIN_INCLUDE_MODELS_ENEMY_H
#define DOMAIN_INCLUDE_MODELS_ENEMY_H

constexpr int INITIAL_GOLD_MIN = 10;
constexpr int INITIAL_GOLD_MAX = 20;
constexpr int INITIAL_PROVISIONS_MAX = 5;

#include <vector>
#include <string>
#include <map>

#include "tile_contents.h"

namespace domain::models {

class Enemy : public TileContents {
 public:
  Enemy(std::string faction, int threat_level);
  ~Enemy() override;

  [[nodiscard]]int GetGold() const;
  [[nodiscard]]int GetProvisions() const;
 private:
  const std::string faction_;
  std::map<int, int> warband_;
  const int gold_;
  const int provisions_;
};

} // namespace domain::models

#endif // DOMAIN_INCLUDE_MODELS_ENEMY_H

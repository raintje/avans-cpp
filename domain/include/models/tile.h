#ifndef DOMAIN_INCLUDE_MODELS_TILE_H
#define DOMAIN_INCLUDE_MODELS_TILE_H

#include <memory>

#include "player.h"

namespace domain::models {
class Tile {
 public:
  void StepOn(Player player);
 private:
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_H

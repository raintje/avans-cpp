#ifndef DOMAIN_INCLUDE_MODELS_TILE_H
#define DOMAIN_INCLUDE_MODELS_TILE_H

#include <memory>

#include "player.h"
#include "enum/tile_type.h"
#include "structs/location.h"

namespace domain::models {
class Tile {
 public:
  [[nodiscard]]virtual structs::Location GetLocation() const = 0;
  [[nodiscard]]virtual char GetDrawChar() const = 0;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_H

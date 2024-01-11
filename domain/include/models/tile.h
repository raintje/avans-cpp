#ifndef DOMAIN_INCLUDE_MODELS_TILE_H
#define DOMAIN_INCLUDE_MODELS_TILE_H

#include <memory>

#include "player.h"
#include "enum/tile_type.h"
#include "structs/location.h"

namespace domain::models {
class Tile {
 public:
  Tile(const structs::Location &location, const enums::TileType &tile_type);
  ~Tile();

  [[nodiscard]]structs::Location GetLocation() const;
  [[nodiscard]]char GetDrawChar() const;
 private:
  structs::Location location_;
  enums::TileType tile_type_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_H

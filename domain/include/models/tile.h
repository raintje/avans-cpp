#ifndef DOMAIN_INCLUDE_MODELS_TILE_H
#define DOMAIN_INCLUDE_MODELS_TILE_H

#include <memory>

#include "structs/location.h"

namespace domain::models {
class Tile {
 public:
  explicit Tile(structs::Location location);
  ~Tile();

  [[nodiscard]]structs::Location GetLocation() const;
  [[nodiscard]]virtual char GetDrawChar() const;
 private:
  structs::Location location_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_H

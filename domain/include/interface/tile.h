#ifndef DOMAIN_INCLUDE_MODELS_TILE_H
#define DOMAIN_INCLUDE_MODELS_TILE_H

#include <memory>

#include "../models/player.h"
#include "../structs/location.h"

namespace domain::interface {
class Tile {
 public:
  virtual void StepOn(models::Player player) = 0;
  [[nodiscard]]structs::Location GetLocation() const { return location_; }
 protected:
  structs::Location location_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_H

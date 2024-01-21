#ifndef DOMAIN_INCLUDE_MODELS_TILE_CONTENTS_H
#define DOMAIN_INCLUDE_MODELS_TILE_CONTENTS_H

#include "player.h"

namespace domain::models {
class TileContents {
 public:
  virtual void Interact() = 0;
  virtual ~TileContents() = default;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_CONTENTS_H

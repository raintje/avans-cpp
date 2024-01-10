#ifndef DOMAIN_INCLUDE_MODELS_CITY_H
#define DOMAIN_INCLUDE_MODELS_CITY_H

#include "interface/tile.h"

namespace domain::models {
class City : public interface::Tile {
 public:
  void StepOn(models::Player player) override;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_CITY_H

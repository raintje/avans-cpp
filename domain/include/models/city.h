#ifndef DOMAIN_INCLUDE_MODELS_CITY_H
#define DOMAIN_INCLUDE_MODELS_CITY_H

#include "encounter.h"

namespace domain::models {
class City : public Encounter {
 public:
  void Interact(models::Player player) override;
};
} // namespace domain::models
#endif //DOMAIN_INCLUDE_MODELS_CITY_H

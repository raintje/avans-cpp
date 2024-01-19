#ifndef DOMAIN_INCLUDE_MODELS_ENCOUNTER_H
#define DOMAIN_INCLUDE_MODELS_ENCOUNTER_H

#include "models/player.h"

namespace domain::models {
class Encounter {
 public:
  virtual void Interact(Player player) = 0;
  virtual ~Encounter() = default;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_ENCOUNTER_H

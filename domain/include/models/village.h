#ifndef DOMAIN_INCLUDE_MODELS_VILLAGE_H
#define DOMAIN_INCLUDE_MODELS_VILLAGE_H

#include "encounter.h"

namespace domain::models {
class Village : public Encounter {
 public:
  void Interact(domain::models::Player player) override;
};
} // namespace domain::models
#endif //DOMAIN_INCLUDE_MODELS_VILLAGE_H

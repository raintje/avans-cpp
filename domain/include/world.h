#ifndef DOMAIN_WORLD_H
#define DOMAIN_WORLD_H

#include <vector>
#include <memory>

#include "province.h"

namespace domain {
class World {
 public:
  World();
 private:
  std::vector<std::unique_ptr<Province>> provinces_;
};
} // namespace domain

#endif //DOMAIN_WORLD_H

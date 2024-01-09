#ifndef DOMAIN_WORLD_H
#define DOMAIN_WORLD_H

#define WORLD_SIZE 4
#define MAX_CITIES 2
#define MAX_VILLAGES 6
#define MAX_MOUNTAINS 4

#include <vector>
#include <memory>

#include "province.h"

namespace domain::models {
class World {
 public:
  World();
  ~World();
 private:
  std::shared_ptr<Province> current_province_;
  std::shared_ptr<Province> previous_province_;
  std::vector<std::shared_ptr<Province>> provinces_;

};
} // namespace domain::models

#endif // DOMAIN_WORLD_H

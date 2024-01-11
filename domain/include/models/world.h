#ifndef DOMAIN_WORLD_H
#define DOMAIN_WORLD_H

#define WORLD_SIZE 4
#define MAX_CITIES 2
#define MAX_VILLAGES 6
#define MAX_MOUNTAINS 4

#include <map>
#include <memory>

#include "structs/location.h"
#include "structs/province_statistics.h"
#include "province.h"

namespace domain::models {
class World {
 public:
  World();
  ~World();
 private:
  std::shared_ptr<Province> current_province_;
  std::shared_ptr<Province> previous_province_;
  std::map<structs::Location, structs::ProvinceStatistics> provinces_;

};
} // namespace domain::models

#endif // DOMAIN_WORLD_H

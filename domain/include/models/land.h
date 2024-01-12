#ifndef DOMAIN_LAND_H
#define DOMAIN_LAND_H

#define LAND_SIZE 4
#define MAX_CITIES 2
#define MAX_VILLAGES 6
#define MAX_MOUNTAINS 4

#include <map>
#include <memory>

#include "structs/location.h"
#include "structs/province_statistics.h"
#include "province.h"

namespace domain::models {
class Land {
 public:
  Land();
  ~Land();
 private:
  std::map<structs::Location, structs::ProvinceStatistics> province_statistics_;
};
} // namespace domain::models

#endif // DOMAIN_LAND_H

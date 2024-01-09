#ifndef DOMAIN_INCLUDE_PROVINCE_H
#define DOMAIN_INCLUDE_PROVINCE_H

#define PROVINCE_SIZE 12

#include <memory>
#include <vector>

#include "random.h"
#include "structs/location.h"
#include "structs/province_statistics.h"
#include "tile.h"

namespace domain::models {

class Province {
 public:
  Province(structs::Location location, structs::ProvinceStatistics province_statistics);
  ~Province();
 private:
  structs::Location location_;
  std::vector<Tile> tiles_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_PROVINCE_H

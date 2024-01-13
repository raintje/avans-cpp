#ifndef DOMAIN_LAND_H
#define DOMAIN_LAND_H

constexpr int LAND_SIZE = 4;
constexpr int MAX_CITIES = 2;
constexpr int MAX_VILLAGES = 6;
constexpr int MAX_MOUNTAINS = 4;

#include <map>
#include <memory>

#include "random_wrapper.h"

#include "structs/location.h"
#include "structs/province_statistics.h"
#include "province.h"

namespace domain::models {
class Land {
 public:
  Land();
  ~Land();

  void EnterProvince(structs::Location location);
 private:
  std::map<structs::Location, structs::ProvinceStatistics> province_statistics_;
  std::unique_ptr<Province> current_province_;
  std::map<structs::Location, std::unique_ptr<Province>> previous_provinces_;
};
} // namespace domain::models

#endif // DOMAIN_LAND_H

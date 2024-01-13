#ifndef DOMAIN_INCLUDE_PROVINCE_H
#define DOMAIN_INCLUDE_PROVINCE_H

constexpr int PROVINCE_SIZE = 12;

#include <memory>
#include <vector>

#include "structs/location.h"
#include "structs/province_statistics.h"
#include "tile.h"

namespace domain::models {

class Province {
 public:
  Province(structs::Location location, structs::ProvinceStatistics province_statistics);
  ~Province();

  /// @brief Getter for the location of the province.
  [[nodiscard]]structs::Location GetLocation() const;

 private:
  structs::Location location_;
  std::vector<std::unique_ptr<Tile>> tiles_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_PROVINCE_H

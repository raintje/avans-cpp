#ifndef DOMAIN_INCLUDE_PROVINCE_H
#define DOMAIN_INCLUDE_PROVINCE_H

constexpr int PROVINCE_SIZE = 12;

#include <utility>
#include <memory>
#include <algorithm>
#include <vector>

#include "structs/province_statistics.h"
#include "enums/tile_type.h"

#include "random_wrapper.h"
#include "db_wrapper.h"

#include "tile.h"
#include "enemy.h"
#include "city.h"
#include "village.h"

namespace domain::models {

class Province {
 public:
  Province(std::pair<int, int> location, structs::ProvinceStatistics province_statistics);
  ~Province();

  /// @brief Getter for the location of the province.
  [[nodiscard]]std::pair<int, int> GetLocation() const;
  /// @brief Getter for a pointer to the Tile vector.
  [[nodiscard]]Tile *GetTileByLocation(std::pair<int, int> location) const;

 private:
  /// @brief Generates the entities on the province map.
  void GenerateProvince(structs::ProvinceStatistics province_statistics);

  /// @brief Randomly generates 1-3 enemies on random empty tiles in the province.
  void GenerateEnemies();

  /// @brief Generates a mountain in a 3x3 radius around the given point.
  void GenerateMountain(std::pair<int, int> location) const;

  std::pair<int, int> location_;
  std::string faction_;
  std::vector<std::unique_ptr<Tile>> tiles_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_PROVINCE_H

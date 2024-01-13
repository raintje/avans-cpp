#include "models/province.h"
#include "models/enemy.h"

namespace domain::models {
Province::Province(structs::Location location,
                   structs::ProvinceStatistics province_statistics) : location_(location) {
  for (int x = 0; x < PROVINCE_SIZE; ++x) {
    for (int y = 0; y < PROVINCE_SIZE; ++y) {
    }
  }
}

structs::Location Province::GetLocation() const { return location_; }

Province::~Province() = default;
} // namespace domain::models
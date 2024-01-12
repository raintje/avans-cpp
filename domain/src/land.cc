#include "models/land.h"

namespace domain::models {
Land::Land() : current_province_(nullptr),
               previous_province_(nullptr) {
  for (int x = 0; x < LAND_SIZE; ++x) {
    for (int y = 0; y < LAND_SIZE; ++y) {
      structs::Location loc = {x, y};
      structs::ProvinceStatistics stats = {util::Random::GetInstance().RandomIntInRange(0, MAX_CITIES),
                                           util::Random::GetInstance().RandomIntInRange(0, MAX_VILLAGES),
                                           util::Random::GetInstance().RandomIntInRange(0, MAX_MOUNTAINS)};
      province_statistics_.emplace(loc, stats);
    }
  }
}
Land::~Land() = default;
} // namespace domain::models
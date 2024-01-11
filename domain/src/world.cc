#include "models/world.h"

namespace domain::models {
World::World() : current_province_(nullptr),
                 previous_province_(nullptr) {
  for (int x = 0; x < WORLD_SIZE; ++x) {
    for (int y = 0; y < WORLD_SIZE; ++y) {
      structs::Location loc = {x, y};
      structs::ProvinceStatistics stats = {util::Random::GetInstance().RandomIntInRange(0, MAX_CITIES),
                                           util::Random::GetInstance().RandomIntInRange(0, MAX_VILLAGES),
                                           util::Random::GetInstance().RandomIntInRange(0, MAX_MOUNTAINS)};
      provinces_.emplace(loc, stats);
    }
  }
}
World::~World() = default;
} // namespace domain::models
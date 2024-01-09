#include "models/province.h"

namespace domain::models {
Province::Province(structs::Location location,
                   structs::ProvinceStatistics province_statistics) : location_(location){
  for (int x = 0; x < PROVINCE_SIZE; ++x) {
    for (int y = 0; y < PROVINCE_SIZE; ++y) {
    }
  }
}

Province::~Province() = default;
} // namespace domain::models
#include <iostream>
#include <utility>

#include "models/province.h"

int main() {
  std::pair<int, int> loc = {0, 0};
  domain::structs::ProvinceStatistics province_statistics = {2, 6, 4};
  auto p = new domain::models::Province(loc, province_statistics);

  for (int x = 0; x < 12; ++x) {
    for (int y = 0; y < 12; ++y) {
      std::pair<int, int> loc_inner = {x, y};
      std::cout << p->GetTileByLocation(loc_inner)->GetDrawChar();
    }
    std::cout << std::endl;
  }

  delete p;
}

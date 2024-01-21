#include "drawing/domain.h"

namespace game::drawing {

static void DrawLand(domain::models::Land *land, std::pair<int, int> selected_province) {
  for (int y = 0; y < LAND_SIZE; ++y) {
    for (int x = 0; x < LAND_SIZE; ++x) {
      auto s = land->GetProvinceStatistics(x, y);

      auto internal_loc = std::make_pair(x, y);

      if (selected_province == internal_loc)
        std::cout << "\033[4m" << s.num_cities << s.num_villages << s.num_mountains << "\033[24m" << " ";
      else std::cout << s.num_cities << s.num_villages << s.num_mountains << " ";

    }
    std::cout << std::endl;
  }
}

static void DrawProvince(domain::models::Province *province) {
  for (int y = 0; y < PROVINCE_SIZE; ++y) {
    for (int x = 0; x < PROVINCE_SIZE; ++x) {
      auto t = province->GetTileByLocation({x, y});
      std::cout << t->GetDrawChar() << " ";
    }
    std::cout << std::endl;
  }
}

void DrawWarband(std::map<int, int> *warband) {
  int counter = 1;
  std::cout << "\033[4m" << "------KRIJGSBENDE------" << "\033[24m" << std::endl;
  for (auto k : *warband) {
    auto t = db::DbWrapper::GetInstance()->GetTroopDataById(k.first);
    std::cout << counter++ << ": " << std::get<3>(t) << std::endl;
    std::cout << "Aantal: " << k.second << " - Totaalprijs: " << std::get<4>(t) * k.second << std::endl;
  }
}

void DrawCityInteraction(domain::models::Village *village) {
  std::cout << "Je benadert de stad, wat zou je willen doen?" << std::endl;
  std::cout << "1. Manschappen rekruteren." << std::endl;
  std::cout << "2. Proviand inslaan." << std::endl;
}

void DrawVillageInteraction(domain::models::Village *village) {
  std::cout << "Je benadert het dorp, wat zou je willen doen?" << std::endl;
  std::cout << "1. Manschappen rekruteren." << std::endl;
  std::cout << "2. Proviand inslaan." << std::endl;
}

} // namespace game::drawing

#include "../../headers/drawing/prompt_drawer.h"

namespace game::drawing {

void PromptDrawer::DrawMap(std::unique_ptr<domain::models::Land> &land) {
  for (int y = 0; y < LAND_SIZE; ++y) {
    for (int x = 0; x < LAND_SIZE; ++x) {
      auto s = land->GetProvinceStatistics(x, y);
      std::cout << s.num_cities << s.num_villages << s.num_mountains << " ";
    }
    std::cout << std::endl;
  }
}

} // namespace game::drawing
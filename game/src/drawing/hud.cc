#include "drawing/hud.h"

namespace game::drawing {

static void DrawStatistics(domain::models::Player *player) {
  std::cout << "Goud: " << player->GetGold() << " Provisies: " << player->GetProvisions() << std::endl;
}

static void ClearConsole() { std::cout << "\x1B[2J\x1B[H"; }

} // namespace game::drawing

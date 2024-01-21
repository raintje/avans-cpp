#include "logic/battle_controller.h"

namespace game::logic {

BattleController::BattleController() = default;
BattleController::~BattleController() = default;

void BattleController::Start(std::map<int, int> *player_warband, std::map<int, int> *enemy_warband) {
  if (drawing::PrintBattlePrompt(true)) Round(*player_warband, *enemy_warband);
  else Retreat(*player_warband, *enemy_warband);
}

void BattleController::Round(std::map<int, int> player_warband, std::map<int, int> enemy_warband) {

}

} // namespace game::logic

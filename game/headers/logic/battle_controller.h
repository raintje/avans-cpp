#ifndef GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H
#define GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H

#include <map>

#include "drawing/logic.h"

namespace game::logic {
class BattleController {
 public:
  BattleController();
  ~BattleController();

  void Start(std::map<int, int> *player_warband, std::map<int, int> *enemy_warband);
  void Round(std::map<int, int> player_warband, std::map<int, int> enemy_warband);
  void Attack(int target, int attacker);
  bool Retreat(std::map<int, int> player_warband, std::map<int, int> enemy_warband);

 private:
  bool battle_ongoing_ = true;
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H

#ifndef GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H
#define GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H

#include <map>
#include <algorithm>

#include "db_wrapper.h"
#include "random_wrapper.h"

#include "drawing/logic.h"

namespace game::logic {
class BattleController {
 public:
  BattleController();
  ~BattleController();

  void Start(std::map<int, int> *player_warband, std::map<int, int> *enemy_warband);
  void Round(const std::map<int, int> &player_warband, const std::map<int, int> &enemy_warband);
  void Retreat(const std::map<int, int> &player_warband, const std::map<int, int> &enemy_warband);

  [[nodiscard]]static bool Attack(int attacker, int target);
  [[nodiscard]]static bool ConfirmDefeat(const std::map<int, int> &warband);

 private:
  static void SubtractLosses(std::map<int, int> warband, const std::pair<int, int> &losses);
  [[nodiscard]]static int FindTarget(const std::map<int, int> &warband);
  [[nodiscard]]static bool CheckTroopType(int id, int volley);

  bool battle_ongoing_;
  std::shared_ptr<drawing::LogicDrawer> logic_drawer_;
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H

#ifndef GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H
#define GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H

#include <map>
#include <algorithm>

#include "logger.h"
#include "validation.h"
#include "db_wrapper.h"
#include "random_wrapper.h"

#include "drawing/logic.h"
#include "models/enemy.h"

namespace game::logic {
class BattleController {
 public:
  explicit BattleController();
  ~BattleController();

  void Start();
  void Round();
  void Retreat();

  [[nodiscard]]bool Attack(int attacker, int target);
  [[nodiscard]]static bool ConfirmDefeat(const std::map<int, int> &warband);

  void SetLogger(const std::shared_ptr<util::Logger> &logger);
  void SetPlayer(domain::models::Player *player);
  void SetEnemy(domain::models::Enemy *enemy);

  void ToggleGodMode();

  void Reset();
 private:
  [[nodiscard]]static int FindTarget(const std::map<int, int> &warband);
  [[nodiscard]]static bool CheckTroopType(int id, int volley);

  domain::models::Player *player_;
  domain::models::Enemy *enemy_;

  int round_;
  bool god_mode_;
  std::shared_ptr<util::Logger> logger_;
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_BATTLE_CONTROLLER_H

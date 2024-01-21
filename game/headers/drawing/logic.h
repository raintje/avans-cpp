#ifndef GAME_HEADERS_DRAWING_LOGIC_H
#define GAME_HEADERS_DRAWING_LOGIC_H

#include <iostream>
#include <string>
#include <map>

#include "models/tile.h"

namespace game::drawing {
class LogicDrawer {
 public:
  LogicDrawer();
  ~LogicDrawer();

  // movement
  void PrintViableMovementOptions(std::map<std::string, domain::models::Tile *> options);

  // vendors
  void PrintTroopTransaction();
  void PrintProvisionTransaction();

  // battle
  [[nodiscard]]static bool PrintBattlePrompt(bool first_turn);
  void PrintAttack(int round, bool friendly, const std::string &troop_type, int amount);
  void PrintTroopDeath(int round, bool friendly, const std::string &troop_type);
};
} // namespace game::drawing

#endif //GAME_HEADERS_DRAWING_LOGIC_H

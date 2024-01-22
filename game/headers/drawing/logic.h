#ifndef GAME_HEADERS_DRAWING_LOGIC_H
#define GAME_HEADERS_DRAWING_LOGIC_H

#include <iostream>
#include <string>
#include <map>

#include "models/tile.h"

namespace game::drawing {
class LogicDrawer {
 public:
  ~LogicDrawer();

  static void PrintAttack(int round, bool friendly, const std::string &attacker_name, const std::string &target_name, bool hit);
  static void PrintTroopDeath(int round, bool friendly, const std::string &troop_name);
 private:
  LogicDrawer();
};
} // namespace game::drawing

#endif //GAME_HEADERS_DRAWING_LOGIC_H

#ifndef GAME_HEADERS_DRAWING_LOGIC_H
#define GAME_HEADERS_DRAWING_LOGIC_H

#include <iostream>
#include <string>
#include <map>

#include "models/tile.h"

namespace game::drawing {
// movement
static void PrintViableMovementOptions(std::map<std::string, domain::models::Tile*> options);

// vendors
static void PrintTroopTransaction();
static void PrintProvisionTransaction();

// battle
[[nodiscard]]static bool PrintBattlePrompt(bool first_turn);
static void PrintAttack(int round, bool friendly, const std::string &troop_type, int amount);
static void PrintTroopDeath(int round, bool friendly, const std::string &troop_type);
} // namespace game::drawing

#endif //GAME_HEADERS_DRAWING_LOGIC_H

#ifndef GAME_HEADERS_DRAWING_HUD_H
#define GAME_HEADERS_DRAWING_HUD_H

#include <iostream>

#include "models/player.h"

namespace game::drawing {
static void DrawStatistics(domain::models::Player *player);
static void ClearConsole();
} // namespace game::drawing

#endif //GAME_HEADERS_DRAWING_HUD_H

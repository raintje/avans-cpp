#ifndef GAME_HEADERS_DRAWING_PROMPT_DRAWER_H
#define GAME_HEADERS_DRAWING_PROMPT_DRAWER_H

#include <iostream>

#include "models/land.h"

namespace game::drawing {

class PromptDrawer {
 public:
  static void DrawMap(std::unique_ptr<domain::models::Land> &land);
};

} // namespace game::drawing

#endif //GAME_HEADERS_DRAWING_PROMPT_DRAWER_H

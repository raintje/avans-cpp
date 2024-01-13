#ifndef GAME_HEADERS_STATE_GAME_H
#define GAME_HEADERS_STATE_GAME_H

#include <memory>
#include <vector>

#include "models/land.h"
#include "../drawing/prompt_drawer.h"

namespace game::state {
class Game {
 public:
  Game();
  ~Game();

  void ChangeLand();
  void RunGame();
 private:
  std::unique_ptr<drawing::PromptDrawer> prompt_drawer_;
  std::unique_ptr<domain::models::Land> current_land_;
  std::vector<std::unique_ptr<domain::models::Land>> previous_lands_;
};
} // namespace game::state

#endif //GAME_HEADERS_STATE_GAME_H

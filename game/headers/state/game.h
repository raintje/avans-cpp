#ifndef GAME_HEADERS_STATE_GAME_H
#define GAME_HEADERS_STATE_GAME_H

#include <memory>
#include <vector>
#include <string>

#include "models/land.h"
#include "drawing/domain.h"
#include "drawing/hud.h"
#include "state/enum/game_state.h"

namespace game::state {
class Game {
 public:
  Game();
  ~Game();

  /// @brief Returns the state of the game.
  enums::GameState GetState();

  /// @brief Sets the state of the game.
  void SetState(enums::GameState state);

  /// @brief Enters a new land.
  void ChangeLand();

  /// @brief Contains the game loop.
  void RunGame();
 private:
  /// @brief Handles text commands.
  void HandleCommand(const std::string &command);

  /// @brief Changes the selected province.
  void ChangeSelectedProvince(const std::string &command);

  bool running_;
  std::unique_ptr<domain::models::Player> player_;
  std::unique_ptr<domain::models::Land> land_;
  std::shared_ptr<drawing::DomainDrawer> domain_drawer_;
  std::pair<int, int> selected_province_;
  enums::GameState state_;
};
} // namespace game::state

#endif //GAME_HEADERS_STATE_GAME_H

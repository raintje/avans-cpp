#ifndef GAME_HEADERS_STATE_GAME_H
#define GAME_HEADERS_STATE_GAME_H

#include <memory>
#include <vector>
#include <string>

#include "logger.h"
#include "models/land.h"
#include "drawing/domain.h"
#include "drawing/hud.h"
#include "state/enum/game_state.h"
#include "logic/battle_controller.h"
#include "logic/movement_controller.h"
#include "logic/interaction_controller.h"

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
  void HandleCommand(std::string command);

  /// @brief Changes the selected province.
  void ChangeSelectedProvince(const std::string &command);

  /// @brief Compiles all the available commands.
  std::vector<std::string> CompileAvailableCommands();

  /// @brief Verifies that the newly selected province is legal.
  [[nodiscard]]static bool CheckIfMiddleProvince(std::pair<int, int> new_location);

  /// @brief Verifies that the king is alive and that the player has troops left.
  void CheckVictoryConditions();

  /// @brief Looks for non-empty tiles in the cardinal directions around the player.
  std::map<std::string, domain::models::Tile *> CheckForInteractableTiles();

  bool running_;
  int turn_counter_;

  // ptrs to data
  std::unique_ptr<domain::models::Player> player_;
  std::unique_ptr<domain::models::Land> land_;

  // controllers
  std::unique_ptr<logic::MovementController> movement_controller_;
  std::unique_ptr<logic::BattleController> battle_controller_;
  std::unique_ptr<logic::InteractionController> interaction_controller_;

  // logging
  std::unique_ptr<util::Logger> logger_;

  std::pair<int, int> selected_province_;
  enums::GameState state_;
};
} // namespace game::state

#endif //GAME_HEADERS_STATE_GAME_H

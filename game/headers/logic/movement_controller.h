#ifndef GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H
#define GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H

#include <vector>
#include <utility>

#include "logger.h"

#include "models/player.h"
#include "models/province.h"

namespace game::logic {
class MovementController {
 public:
  MovementController();
  ~MovementController();

  void SetLogger(const std::shared_ptr<util::Logger> &logger);

  [[nodiscard]]static std::vector<std::string> CheckViableMoves(domain::models::Province *province,
                                                                std::pair<int, int> original_position);
  void MovePlayer(domain::models::Player *player,
                  domain::models::Province *province,
                  int turn_counter,
                  std::pair<int, int> new_location);

  static void MoveAllEnemies(domain::models::Province *province);

  static std::pair<int, int> PrepareNextLocation(const std::string &command, domain::models::Player *p);
  static bool CheckIfMovementCommand(const std::string &command);
 private:
  std::shared_ptr<util::Logger> logger_;
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H

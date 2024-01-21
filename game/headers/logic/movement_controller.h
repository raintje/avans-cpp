#ifndef GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H
#define GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H

#include <vector>
#include <utility>

#include "models/player.h"
#include "models/province.h"

namespace game::logic {
class MovementController {
 public:
  MovementController();
  ~MovementController();

  [[nodiscard]]std::vector<std::string> CheckViableMoves(domain::models::Province *province,
                                                         std::pair<int, int> original_position);
  void MovePlayer(domain::models::Player *player, domain::models::Province *province, std::pair<int, int> new_location);
  std::pair<int, int> PrepareNextLocation(const std::string &command, domain::models::Player *p);
  bool CheckIfMovementCommand(const std::string &command);
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H

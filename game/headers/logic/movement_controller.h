#ifndef GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H
#define GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H

#include <map>
#include <utility>

#include "models/province.h"

namespace game::logic {
class MovementController {
 public:
  MovementController();
  ~MovementController();

  [[nodiscard]]std::map<std::string, domain::models::Tile *> CheckViableMoves(domain::models::Province *province,
                                                                              std::pair<int, int> original_position);
  void MovePlayerToTile(domain::models::Tile *start,
                        domain::models::Tile *destination,
                        std::unique_ptr<domain::models::Player> &player);
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_MOVEMENT_CONTROLLER_H

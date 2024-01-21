#include "logic/movement_controller.h"

namespace game::logic {

MovementController::MovementController() = default;
MovementController::~MovementController() = default;

std::map<std::string, domain::models::Tile *> MovementController::CheckViableMoves(domain::models::Province *province,
                                                                                   std::pair<int,
                                                                                             int> original_position) {
  std::map<std::string, domain::models::Tile *> result;

  if (original_position.first - 1 >= 0) {
    auto left = province->GetTileByLocation({original_position.first - 1, original_position.second});
    if (left->GetType() == domain::enums::EMPTY) result.insert({"left", left});
  }

  if (original_position.first + 1 < PROVINCE_SIZE) {
    auto right = province->GetTileByLocation({original_position.first + 1, original_position.second});
    if (right->GetType() == domain::enums::EMPTY) result.insert({"right", right});
  }

  if (original_position.second - 1 >= 0) {
    auto up = province->GetTileByLocation({original_position.first, original_position.second - 1});
    if (up->GetType() == domain::enums::EMPTY) result.insert({"up", up});
  }

  if (original_position.second + 1 < PROVINCE_SIZE) {
    auto down = province->GetTileByLocation({original_position.first, original_position.second + 1});
    if (down->GetType() == domain::enums::EMPTY) result.insert({"down", down});
  }

  return result;
}

void MovementController::MovePlayerToTile(domain::models::Tile *start,
                                          domain::models::Tile *destination,
                                          std::unique_ptr<domain::models::Player> &player) {
  start->SetType(domain::enums::EMPTY);
  destination->SetType(domain::enums::PLAYER);
  destination->SetTileContents(std::move(player));
}

} // namespace domain::logic

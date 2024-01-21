#include "logic/movement_controller.h"

namespace game::logic {

MovementController::MovementController() = default;
MovementController::~MovementController() = default;

std::vector<std::string> MovementController::CheckViableMoves(domain::models::Province *province,
                                                              std::pair<int, int> original_position) {
  std::vector<std::string> result;

  if (original_position.first - 1 >= 0) {
    auto left = province->GetTileByLocation({original_position.first - 1, original_position.second});
    if (left->GetType() == domain::enums::EMPTY) result.emplace_back("a - beweeg een vakje naar boven");
  }

  if (original_position.first + 1 < PROVINCE_SIZE) {
    auto right = province->GetTileByLocation({original_position.first + 1, original_position.second});
    if (right->GetType() == domain::enums::EMPTY) result.emplace_back("d - beweeg een vakje naar links");
  }

  if (original_position.second - 1 >= 0) {
    auto up = province->GetTileByLocation({original_position.first, original_position.second - 1});
    if (up->GetType() == domain::enums::EMPTY) result.emplace_back("w - beweeg een vakje naar boven");
  }

  if (original_position.second + 1 < PROVINCE_SIZE) {
    auto down = province->GetTileByLocation({original_position.first, original_position.second + 1});
    if (down->GetType() == domain::enums::EMPTY) result.emplace_back("s - beweeg een vakje naar beneden");
  }

  return result;
}

void MovementController::MovePlayer(domain::models::Player *player,
                                    domain::models::Province *province,
                                    std::pair<int, int> new_location) {
  auto prev = player->GetLocation();
  auto t = province->GetTileByLocation(prev);
  if (t != nullptr) t->SetType(domain::enums::EMPTY);

  auto next = province->GetTileByLocation(new_location);
  next->SetType(domain::enums::PLAYER);
  player->SetLocation(std::move(new_location));
}

std::pair<int, int> MovementController::PrepareNextLocation(const std::string &command, domain::models::Player *p) {
  auto temp = p->GetLocation();
  std::pair<int, int> next = temp;

  if (command == "w") {
    if (temp.second - 1 >= 0) next = std::make_pair(temp.first, temp.second - 1);
  }
  if (command == "s") {
    if (temp.second + 1 < PROVINCE_SIZE) next = std::make_pair(temp.first, temp.second + 1);
  }
  if (command == "a") {
    if (temp.first - 1 >= 0) next = std::make_pair(temp.first - 1, temp.second);
  }
  if (command == "d") {
    if (temp.first + 1 < PROVINCE_SIZE) next = std::make_pair(temp.first + 1, temp.second);
  }

  return next;
}

bool MovementController::CheckIfMovementCommand(const std::string &command) {
  if (command == "w") return true;
  if (command == "a") return true;
  if (command == "s") return true;
  if (command == "d") return true;
  return false;
}

} // namespace domain::logic

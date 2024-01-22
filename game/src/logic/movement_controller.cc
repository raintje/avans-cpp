#include "logic/movement_controller.h"

namespace game::logic {

MovementController::MovementController() = default;
MovementController::~MovementController() = default;

void MovementController::SetLogger(const std::shared_ptr<util::Logger> &logger) { logger_ = logger; }

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
                                    int turn_counter,
                                    std::pair<int, int> new_location) {
  auto prev = player->GetLocation();
  auto t = province->GetTileByLocation(prev);
  if (t != nullptr) t->SetType(domain::enums::EMPTY);

  auto next = province->GetTileByLocation(new_location);
  next->SetType(domain::enums::PLAYER);
  player->SetLocation(std::move(new_location));

  logger_->WriteLine(
      "Beurt " + std::to_string(turn_counter) + ": Speler heeft van tegel [" + std::to_string(prev.first)
          + ", "
          + std::to_string(prev.second) + "] naar tegel [" + std::to_string(player->GetLocation().first) + ", "
          + std::to_string(player->GetLocation().second) + "] bewogen.");
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

void MovementController::MoveAllEnemies(domain::models::Province *province) {
  auto enemies = province->GetTilesByType(domain::enums::ENEMY);
  for (auto &i : enemies) {
    auto temp = i->GetLocation();
    bool horizontal = util::RandomWrapper::GetInstance()->RandomIntInRange(0, 100) > 50;

    if (horizontal) {
      auto left = std::make_pair(temp.first - 1, temp.second);
      auto right = std::make_pair(temp.first + 1, temp.second);

      if (left.first >= 0) {
        auto left_tile = province->GetTileByLocation(left);
        if (left_tile->GetType() == domain::enums::EMPTY) {
          left_tile->SetTileContents(i->MoveContents());
          left_tile->SetType(domain::enums::ENEMY);
          i->SetTileContents(nullptr);
          i->SetType(domain::enums::EMPTY);
          return;
        }
      } else if (right.first < PROVINCE_SIZE) {
        auto right_tile = province->GetTileByLocation(right);
        if (right_tile->GetType() == domain::enums::EMPTY) {
          right_tile->SetTileContents(i->MoveContents());
          right_tile->SetType(domain::enums::ENEMY);
          i->SetTileContents(nullptr);
          i->SetType(domain::enums::EMPTY);
          return;
        }
      }
    } else {
      auto up = std::make_pair(temp.first, temp.second - 1);
      auto down = std::make_pair(temp.first, temp.second + 1);

      if (up.second >= 0) {
        auto up_tile = province->GetTileByLocation(up);
        if (up_tile->GetType() == domain::enums::EMPTY) {
          up_tile->SetTileContents(i->MoveContents());
          up_tile->SetType(domain::enums::ENEMY);
          i->SetTileContents(nullptr);
          i->SetType(domain::enums::EMPTY);
        }
      } else if (down.second < PROVINCE_SIZE) {
        auto down_tile = province->GetTileByLocation(down);
        if (down_tile->GetType() == domain::enums::EMPTY) {
          down_tile->SetTileContents(i->MoveContents());
          down_tile->SetType(domain::enums::ENEMY);
          i->SetTileContents(nullptr);
          i->SetType(domain::enums::EMPTY);
        }
      }
    }
  }
}

} // namespace domain::logic

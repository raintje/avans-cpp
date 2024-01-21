#include "state/game.h"

namespace game::state {

Game::Game() :
    running_(true),
    turn_counter_(1),
    player_(std::make_unique<domain::models::Player>()),
    state_(enums::SHOWING_LAND),
    land_(std::make_unique<domain::models::Land>()),
    selected_province_({0, 0}),
    movement_controller_(std::make_unique<logic::MovementController>()),
    interaction_controller_(std::make_unique<logic::InteractionController>()),
    battle_controller_(std::make_unique<logic::BattleController>()),
    logger_(std::make_unique<util::Logger>()) {}
Game::~Game() = default;

void Game::ChangeLand() {
  drawing::DomainDrawer::DrawLand(land_.get(), selected_province_);
  std::cout << "Weet je zeker dat je van land wil wisselen? (Y/N): ";

  std::string input;
  std::getline(std::cin, input);
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);

  if (input == "y") {
    land_ = std::make_unique<domain::models::Land>();
    selected_province_ = {0, 0};
    logger_->WriteLine("Beurt " + std::to_string(turn_counter_++) + ": Speler is naar een ander land gegaan.");
  }
}

void Game::RunGame() {
  while (running_) {
    drawing::HudDrawer::ClearConsole();

    if (GetState() == enums::SHOWING_LAND) drawing::DomainDrawer::DrawLand(land_.get(), selected_province_);
    if (GetState() == enums::SHOWING_PROVINCE) drawing::DomainDrawer::DrawProvince(land_->GetCurrentProvince());
    if (GetState() == enums::SHOWING_WARBAND) {
      drawing::DomainDrawer::DrawWarband(player_.get());
    }

    for (const auto &s : CompileAvailableCommands()) {
      std::cout << s << std::endl;
    }

    std::cout << "Voer een commando uit:  ";

    std::string input;
    std::getline(std::cin, input);
    HandleCommand(input);
  }
}

void Game::HandleCommand(std::string command) {
  auto i = std::move(command);
  std::transform(i.begin(), i.end(), i.begin(), ::tolower);

  if (i == "stop") {
    logger_->WriteLine("Beurt " + std::to_string(turn_counter_) + ": Speler heeft het spel gesloten.");
    running_ = false;
  }
  if (i == "m") SetState(enums::SHOWING_LAND);
  if (i == "b") SetState(enums::SHOWING_WARBAND);
  if (i == "p" && land_->GetCurrentProvince() != nullptr) SetState(enums::SHOWING_PROVINCE);

  if (i == "c" && GetState() == enums::SHOWING_LAND) {
    ChangeLand();
  }

  if (movement_controller_->CheckIfMovementCommand(i)) {
    if (GetState() == enums::SHOWING_LAND && land_->GetCurrentProvince() == nullptr) {
      auto temp = selected_province_;
      ChangeSelectedProvince(i);
      logger_->WriteLine("Beurt " + std::to_string(turn_counter_++) + ": Speler heeft de geselecteerde provincie van ["
                             + std::to_string(temp.first) + ", " + std::to_string(temp.second) + "] naar ["
                             + std::to_string(selected_province_.first) + ", "
                             + std::to_string(selected_province_.second) + "] veranderd.");
    }

    if (GetState() == enums::SHOWING_PROVINCE) {
      auto next_loc = movement_controller_->PrepareNextLocation(i, player_.get());
      auto t = land_->GetCurrentProvince()->GetTileByLocation(next_loc);
      if (t->GetType() == domain::enums::EMPTY) {
        auto temp = player_->GetLocation();
        movement_controller_->MovePlayer(player_.get(),
                                         land_->GetCurrentProvince(),
                                         next_loc);
        logger_->WriteLine(
            "Beurt " + std::to_string(turn_counter_++) + ": Speler heeft van tegel [" + std::to_string(temp.first)
                + ", "
                + std::to_string(temp.second) + "] naar tegel [" + std::to_string(player_->GetLocation().first) + ", "
                + std::to_string(player_->GetLocation().second) + "] bewogen.");
      } else {
        if (t->GetType() == domain::enums::VILLAGE)
          interaction_controller_->HandleVillageInteraction(player_.get(), logger_.get(), turn_counter_++, t);

        if (t->GetType() == domain::enums::CITY)
          interaction_controller_->HandleCityInteraction(player_.get(), logger_.get(), turn_counter_++, t);

        if (t->GetType() == domain::enums::ENEMY) {
          auto e = reinterpret_cast<domain::models::Enemy *>(t->GetTileContents());
          e->Interact();
          battle_controller_->Start(player_->GetWarband(), e->GetWarband());
          CheckVictoryConditions();

        }
      }
    }
  }

  if (i == "g" && GetState() == enums::SHOWING_LAND && land_->GetCurrentProvince() == nullptr) {
    land_->EnterProvince(selected_province_, player_.get());
    SetState(enums::SHOWING_PROVINCE);
    logger_->WriteLine("Beurt " + std::to_string(turn_counter_++) + ": Speler heeft provincie op locatie ["
                           + std::to_string(selected_province_.first) + ", "
                           + std::to_string(selected_province_.second) + "] betreedt.");
  }
}

std::vector<std::string> Game::CompileAvailableCommands() {
  std::vector<std::string> result;

  std::string show_warband = "b - inspecteer je eigen krijgsbende";
  std::string show_province = "p - toon de huidige provincie";
  std::string show_land = "m - toon de kaart van het huidige land";

  if (GetState() == enums::SHOWING_WARBAND) {
    result.emplace_back(std::move(show_land));
    if (land_->GetCurrentProvince() != nullptr) result.emplace_back(std::move(show_province));
  }

  if (GetState() == enums::SHOWING_PROVINCE) {
    result.emplace_back(std::move(show_warband));
    result.emplace_back(std::move(show_land));
    auto v = movement_controller_->CheckViableMoves(land_->GetCurrentProvince(), player_->GetLocation());
    for (auto r : v) {
      result.emplace_back(std::move(r));
    }

    auto t = CheckForInteractableTiles();

    if (t.contains("up"))
      result.emplace_back("w - benader de tegel ten noorde van je.");
    if (t.contains("down"))
      result.emplace_back("s - benader de tegel ten zuide van je.");
    if (t.contains("left"))
      result.emplace_back("a - benader de tegel ten westen van je.");
    if (t.contains("right"))
      result.emplace_back("d - benader de tegel ten right van je.");
  }

  if (GetState() == enums::SHOWING_LAND) {
    if (land_->GetCurrentProvince() != nullptr) {
      result.emplace_back(std::move(show_province));
    } else {
      result.emplace_back("wasd - verander selectie van provincie (binnenste provincies niet benaderbaar)");
    }

    result.emplace_back(std::move(show_warband));
    result.emplace_back("c - reis naar een ander land");
  }

  return result;
}

bool Game::CheckIfMiddleProvince(std::pair<int, int> new_location) {
  if (new_location == std::make_pair(1, 1)) return true;
  if (new_location == std::make_pair(1, 2)) return true;
  if (new_location == std::make_pair(2, 1)) return true;
  if (new_location == std::make_pair(2, 2)) return true;
  return false;
}

void Game::ChangeSelectedProvince(const std::string &command) {

  auto temp = selected_province_;

  if (command == "a") {
    if (temp.first - 1 >= 0)
      temp = {temp.first - 1, temp.second};
  }

  if (command == "d") {
    if (temp.first + 1 < LAND_SIZE)
      temp = {temp.first + 1, temp.second};
  }

  if (command == "w") {
    if (temp.second - 1 >= 0)
      temp = {temp.first, temp.second - 1};
  }

  if (command == "s") {
    if (temp.second + 1 < LAND_SIZE)
      temp = {temp.first, temp.second + 1};
  }

  if (!CheckIfMiddleProvince(temp)) {
    selected_province_ = std::move(temp);
  }

}

std::map<std::string, domain::models::Tile *> Game::CheckForInteractableTiles() {
  std::map<std::string, domain::models::Tile *> result;
  auto temp = player_->GetLocation();

  auto left = std::make_pair(temp.first - 1, temp.second);
  if (left.first >= 0) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(left);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("left", t);
  }

  auto right = std::make_pair(temp.first + 1, temp.second);
  if (right.first < PROVINCE_SIZE) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(right);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("right", t);
  }

  auto up = std::make_pair(temp.first, temp.second - 1);
  if (up.second >= 0) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(up);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("up", t);
  }

  auto down = std::make_pair(temp.first, temp.second + 1);
  if (down.second < PROVINCE_SIZE) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(down);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("down", t);
  }

  return result;
}

void Game::CheckVictoryConditions() {
  // @TODO check if king is dead or if troops are dead
}

enums::GameState Game::GetState() { return state_; }
void Game::SetState(enums::GameState state) { state_ = state; }

} // namespace game::state
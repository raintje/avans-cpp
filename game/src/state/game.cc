#include "state/game.h"

namespace game::state {

Game::Game() :
    running_(true),
    player_(std::make_unique<domain::models::Player>()),
    state_(enums::SHOWING_LAND),
    land_(std::make_unique<domain::models::Land>()),
    selected_province_({0, 0}) {}
Game::~Game() = default;

void Game::ChangeLand() {
  land_ = std::make_unique<domain::models::Land>();
}

void Game::RunGame() {
  while (running_) {
    drawing::DrawStatistics(player_.get());
    switch (state_) {
      case enums::SHOWING_LAND:drawing::DrawLand(land_.get(), selected_province_);
        break;
      case enums::SHOWING_PROVINCE:drawing::DrawProvince(land_->GetCurrentProvince());
        break;
      case enums::SHOWING_WARBAND:drawing::DrawWarband(player_->GetWarband());
        break;
    }
    std::string input;
    std::cout << "Type een commando: ";
    std::getline(std::cin, input);
    drawing::ClearConsole();
    ChangeSelectedProvince(input);
  }
}

void Game::HandleCommand(const std::string &command) {
  if (command == "stop") running_ = false;
  if (command == "toon krijgsbende") SetState(enums::SHOWING_WARBAND);
  if (command == "toon kaart") SetState(enums::SHOWING_LAND);
  if (command == "toon provincie") {
    if (land_->GetCurrentProvince() != nullptr)
      SetState(enums::SHOWING_PROVINCE);
    else
      std::cout << "Nog geen provincie geselecteerd." << std::endl;
  }
}

void Game::ChangeSelectedProvince(const std::string &command) {
  if (command == "a") {
    if (selected_province_.first - 1 >= 0)
      selected_province_ = {selected_province_.first - 1, selected_province_.second};
  }

  if (command == "d") {
    if (selected_province_.first + 1 < LAND_SIZE)
      selected_province_ = {selected_province_.first + 1, selected_province_.second};
  }

  if (command == "w") {
    if (selected_province_.second - 1 >= 0)
      selected_province_ = {selected_province_.first, selected_province_.second - 1};
  }

  if (command == "s") {
    if (selected_province_.second + 1 < LAND_SIZE)
      selected_province_ = {selected_province_.first, selected_province_.second + 1};
  }

  if (command == "g") {
    land_->EnterProvince(selected_province_);
    SetState(enums::SHOWING_PROVINCE);
  }
}

enums::GameState Game::GetState() { return state_; }
void Game::SetState(enums::GameState state) { state_ = state; }

} // namespace game::state
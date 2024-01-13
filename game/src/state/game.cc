#include "../../headers/state/game.h"

namespace game::state {

Game::Game() :
    current_land_(std::make_unique<domain::models::Land>()),
    prompt_drawer_(std::make_unique<drawing::PromptDrawer>()) {}
Game::~Game() = default;

void Game::ChangeLand() {
  previous_lands_.push_back(std::move(current_land_));
  current_land_ = std::make_unique<domain::models::Land>();
}

void Game::RunGame() {
  prompt_drawer_->DrawMap(current_land_);
}

} // namespace game::state
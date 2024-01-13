#include "../../headers/state/game.h"

namespace game::state {

Game::Game() : current_land_(std::make_unique<domain::models::Land>()) {}
Game::~Game() = default;

} // namespace game::state
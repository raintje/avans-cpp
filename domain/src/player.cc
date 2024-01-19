#include "../include/models/player.h"

namespace domain::models {

int Player::GetGold() const { return gold_; }
int Player::GetProvisions() const { return provisions_; }

Player::Player(std::pair<int, int> location) :
    gold_(STARTING_GOLD),
    provisions_(STARTING_PROVISIONS),
    location_(std::move(location)) {}

Player::~Player() = default;

} // namespace domain::models

#include "../include/models/player.h"

namespace domain::models {

int Player::GetGold() const { return gold_; }
int Player::GetProvisions() const { return provisions_; }

char Player::GetDrawChar() const { return 'K'; }

Player::Player(structs::Location location) :
    Tile(location),
    gold_(STARTING_GOLD),
    provisions_(STARTING_PROVISIONS) {}

Player::~Player() = default;

} // namespace domain::models

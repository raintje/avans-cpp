#include "../include/models/player.h"

namespace domain::models {

int Player::GetGold() const { return gold_; }
void Player::ReduceGoldBy(int gold) { gold_ -= gold; }
void Player::IncreaseGoldBy(int gold) { gold_ += gold; }

int Player::GetProvisions() const { return provisions_; }
void Player::ReduceProvisionsBy(int provisions) { provisions_ -= provisions; }
void Player::IncreaseProvisionsBy(int provisions) { provisions_ += provisions; }

std::map<int, int> *Player::GetWarband() { return &warband_; }
void Player::AddTroops(int id) {
  if (warband_.contains(id)) warband_[id]++;
  else warband_.insert({id, 1});
}

Player::Player() :
    gold_(STARTING_GOLD),
    provisions_(STARTING_PROVISIONS) {
  auto troop_amount = util::RandomWrapper::GetInstance()->RandomIntInRange(1, 5);
  for (int i = 0; i <= troop_amount; ++i) {
    auto id = util::RandomWrapper::GetInstance()->RandomIntInRange(1,
                                                                   static_cast<int>(db::DbWrapper::GetInstance()->GetTroopTypes().size()));
    AddTroops(id);
  }
}

Player::~Player() = default;

} // namespace domain::models

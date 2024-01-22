#include <utility>

#include "../include/models/player.h"

namespace domain::models {

int Player::GetGold() const { return gold_; }
void Player::ReduceGoldBy(int gold) { gold_ -= gold; }
void Player::IncreaseGoldBy(int gold) { gold_ += gold; }

int Player::GetProvisions() const { return provisions_; }
void Player::ReduceProvisionsBy(int provisions) { provisions_ -= provisions; }
void Player::IncreaseProvisionsBy(int provisions) { provisions_ += provisions; }
void Player::Upkeep() {
  for (auto &i : warband_) {
    if (provisions_ > 0) {
      ReduceProvisionsBy(i.second);
    }
    else if (util::RandomWrapper::GetInstance()->RandomIntInRange(0, 100) > 90) {
      i.second--;
      if (i.second >= 0) warband_.erase(i.first);
    }
  }
}

std::map<int, int> *Player::GetWarband() { return &warband_; }
void Player::AddTroops(int id, int amount) {
  if (warband_.contains(id)) warband_[id] += amount;
  else warband_.insert({id, amount});
}
void Player::RemoveTroops(int id, int amount) {
  warband_[id] -= amount;
  if (warband_[id] >= 0) warband_.erase(id);
}

Player::Player() :
    gold_(STARTING_GOLD),
    provisions_(STARTING_PROVISIONS) {
  auto troop_amount = util::RandomWrapper::GetInstance()->RandomIntInRange(1, 5);
  for (int i = 0; i <= troop_amount; ++i) {
    auto id = util::RandomWrapper::GetInstance()->RandomIntInRange(1,
                                                                   static_cast<int>(db::DbWrapper::GetInstance()->GetTroopTypes().size()));
    AddTroops(id, 1);
  }
}

void Player::SetLocation(std::pair<int, int> location) { location_ = std::move(location); }
std::pair<int, int> Player::GetLocation() { return location_; }

void Player::SetProvince(const std::pair<int, int> &province) { current_province_ = province; }
std::pair<int, int> Player::GetProvince() { return current_province_; }

Player::~Player() = default;

} // namespace domain::models

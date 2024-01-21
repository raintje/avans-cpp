#include "models/king.h"

namespace domain::models {

King::~King() = default;
King::King() : province_(std::make_pair(util::RandomWrapper::GetInstance()->RandomIntInRange(1, 2),
                                        util::RandomWrapper::GetInstance()->RandomIntInRange(1, 2))) {
  auto t = db::DbWrapper::GetInstance()->GetThreatLevel(KING_THREAT_LEVEL);
  auto tc = util::RandomWrapper::GetInstance()->RandomIntInRange(t.first, t.second);
  auto f = db::DbWrapper::GetInstance()->GetFactions();

  for (int i = 0; i < tc; ++i) {
    auto faction_random = util::RandomWrapper::GetInstance()->RandomItemFromVector(f);
    auto id = db::DbWrapper::GetInstance()->GetTroopIdByFaction(faction_random);

    if (warband_.contains(id)) warband_[id]++;
    else warband_.emplace(id, 1);
  }
}

std::map<int, int> King::GetWarband() { return warband_; }
std::pair<int, int> King::GetProvince() { return province_; }
std::pair<int, int> King::GetLocation() { return location_; }
void King::SetLocation(std::pair<int, int> location) { location_ = std::move(location); }

} // namespace domain::models

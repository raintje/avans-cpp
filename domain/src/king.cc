#include "models/king.h"

namespace domain::models {

King::King(structs::Location location) : Tile(location) {
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

char King::GetDrawChar() const { return '$'; }

} // namespace domain::models

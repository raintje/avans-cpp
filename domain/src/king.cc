#include "models/king.h"
#include "random.h"

namespace domain::models {

King::King(structs::Location province, structs::Location position) :
    province_(province),
    position_(position) {
  auto t = db::DbWrapper::GetInstance()->GetThreatLevel(KING_THREAT_LEVEL);
  auto tc = util::Random::GetInstance()->RandomIntInRange(t.first, t.second);
  auto f = db::DbWrapper::GetInstance()->GetFactions();

  for (int i = 0; i < tc; ++i) {
    auto fi = util::Random::GetInstance()->RandomItemFromVector(f);
    auto id = db::DbWrapper::GetInstance()->GetTroopIdByFaction(fi);

    if (warband_.contains(id)) warband_[id]++;
    else warband_.emplace(id, 1);
  }

}
} // namespace domain::models

#include <utility>

#include "models/enemy.h"
#include "db_wrapper.h"
#include "random_wrapper.h"

namespace domain::models {

Enemy::Enemy(std::string faction, const int threat_level) :
    faction_(std::move(faction)),
    gold_(util::RandomWrapper::GetInstance()->RandomIntInRange(INITIAL_GOLD_MIN, INITIAL_GOLD_MAX)),
    provisions_(util::RandomWrapper::GetInstance()->RandomIntInRange(0, INITIAL_PROVISIONS_MAX)) {
  auto t = db::DbWrapper::GetInstance()->GetThreatLevel(threat_level);
  int troop_count = util::RandomWrapper::GetInstance()->RandomIntInRange(t.first, t.second);
  troops_.emplace(db::DbWrapper::GetInstance()->GetTroopIdByFaction(faction_), troop_count);
}

void Enemy::Interact(models::Player player) {

}

} // namespace domain::models
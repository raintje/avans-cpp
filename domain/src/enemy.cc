#include "models/enemy.h"
#include "db_wrapper.h"

namespace domain::models {

Enemy::Enemy(structs::Location location, const std::string &faction, const int troop_count) :
    location_(location),
    faction_(faction) {
  troops_.emplace(db::DbWrapper::GetInstance()->GetTroopIdByFaction(faction_), troop_count);
}

structs::Location Enemy::GetLocation() const { return location_; }
char Enemy::GetDrawChar() const { return '*'; }

} // namespace domain::models
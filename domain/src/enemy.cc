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
  warband_.emplace(db::DbWrapper::GetInstance()->GetTroopIdByFaction(faction_), troop_count);
}

std::map<int, int> *Enemy::GetWarband() { return &warband_; }
int Enemy::GetGold() const { return gold_; }
int Enemy::GetProvisions() const { return provisions_; }

void Enemy::Interact() {
  std::cout << "Je bent een vijandige krijgsbende tegengekomen! Wat wil je doen?" << std::endl;
  std::cout << "1. Vechten" << std::endl;
  std::cout << "2. Inspecteren" << std::endl;
  std::cout << "3. Terugtrekken" << std::endl;
  std::cout << "Voer hier je antwoord in (1, 2, 3): ";
}

Enemy::~Enemy() = default;

} // namespace domain::models
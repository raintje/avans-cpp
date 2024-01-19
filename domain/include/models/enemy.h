#ifndef DOMAIN_INCLUDE_MODELS_ENEMY_H
#define DOMAIN_INCLUDE_MODELS_ENEMY_H

constexpr int INITIAL_GOLD_MIN = 10;
constexpr int INITIAL_GOLD_MAX = 20;
constexpr int INITIAL_PROVISIONS_MAX = 5;

#include <vector>
#include <string>
#include <map>

#include "encounter.h"

namespace domain::models {

class Enemy : public Encounter {
 public:
  Enemy(std::string faction, int threat_level);
  void Interact(models::Player player) override;
 private:
  const std::string faction_;
  std::map<int, int> troops_;
  const int gold_;
  const int provisions_;
};

} // namespace domain::models

#endif // DOMAIN_INCLUDE_MODELS_ENEMY_H

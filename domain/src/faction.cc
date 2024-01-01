#include "../include/faction.h"

namespace domain {

Faction::Faction() = default;
Faction::~Faction() = default;

std::string Faction::GetName() const {
  return name_;
}

} // namespace domain

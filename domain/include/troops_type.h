#ifndef DOMAIN_INCLUDE_TROOPS_TYPE_H
#define DOMAIN_INCLUDE_TROOPS_TYPE_H

#include <stdexcept>

namespace domain {
enum class TroopsType {
  HORSE_ARCHER,
  ARCHER,
  SPEAR_FIGHTER,
  CAVALRY,
  INFANTRY,
};

static TroopsType STRING_TO_TROOPS_TYPE(const std::string &type) {
  if (type == "paardschutter") return TroopsType::HORSE_ARCHER;
  if (type == "boogschutter") return TroopsType::ARCHER;
  if (type == "speerdrager") return TroopsType::SPEAR_FIGHTER;
  if (type == "cavalerie") return TroopsType::CAVALRY;
  if (type == "infanterie") return TroopsType::INFANTRY;
  else throw std::invalid_argument("[STRING_TO_TROOPS_TYPE]: Invalid argument passed.");
}

} // namespace domain

#endif //DOMAIN_INCLUDE_TROOPS_TYPE_H

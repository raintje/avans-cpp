#ifndef DOMAIN_INCLUDE_TROOPS_H
#define DOMAIN_INCLUDE_TROOPS_H

#include <string>
#include <memory>
#include <utility>

#include "faction.h"
#include "troops_type.h"

namespace domain {

class Troops {
 public:
  Troops(std::string name,
         const std::string &type,
         Faction *faction,
         float price);
  ~Troops();

  std::shared_ptr<Faction> GetFaction() const;
  TroopsType GetType() const;
  std::string GetName() const;
  float GetPrice() const;

 private:
  std::shared_ptr<Faction> faction_;
  TroopsType type_;
  std::string name_;
  float price_{};
};

} // namespace domain

#endif //DOMAIN_INCLUDE_TROOPS_H

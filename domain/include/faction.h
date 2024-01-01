#ifndef SRC_DOMAIN_SRC_FACTION_H
#define SRC_DOMAIN_SRC_FACTION_H

#include <string>

namespace domain {
class Faction {
 public:
  Faction();
  ~Faction();

  std::string GetName() const;
 private:
  std::string name_;

};
} // namespace domain

#endif //SRC_DOMAIN_SRC_FACTION_H

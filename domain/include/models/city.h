#ifndef DOMAIN_INCLUDE_MODELS_CITY_H
#define DOMAIN_INCLUDE_MODELS_CITY_H

constexpr int MIN_TROOPS_CITY = 2;
constexpr int MAX_TROOPS_CITY = 20;
constexpr int PROVISION_PRICE_CITY = 2;

#include <string>

#include "db_wrapper.h"
#include "random_wrapper.h"

#include "tile_contents.h"
#include "player.h"

namespace domain::models {
class City : public TileContents {
 public:
  explicit City(const std::string &faction);
  ~City() override;

  void Interact() override;

  [[nodiscard]]int GetTroopId() const;
  [[nodiscard]]int GetTroopCount() const;

  void BuyTroops(Player *p, int amount) const;
  void BuyProvisions(Player *p, int amount) const;
 private:
  std::pair<int, int> troops_;
};
} // namespace domain::models
#endif //DOMAIN_INCLUDE_MODELS_CITY_H

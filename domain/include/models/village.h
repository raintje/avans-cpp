#ifndef DOMAIN_INCLUDE_MODELS_VILLAGE_H
#define DOMAIN_INCLUDE_MODELS_VILLAGE_H

constexpr int MIN_TROOPS_VILLAGE = 1;
constexpr int MAX_TROOPS_VILLAGE = 10;
constexpr int MIN_PROVISIONS_VILLAGE = 10;
constexpr int MAX_PROVISIONS_VILLAGE = 100;
constexpr int PROVISION_PRICE_VILLAGE = 1;

#include "player.h"
#include "tile_contents.h"

namespace domain::models {
class Village : public TileContents {
 public:
  explicit Village(const std::string &faction);
  ~Village() override;

  void Interact() override;

  [[nodiscard]]int GetTroopId() const;
  [[nodiscard]]int GetTroopCount() const;
  [[nodiscard]]int GetProvisions() const;

  void BuyTroops(Player *p, int amount) const;
  void BuyProvisions(Player *p, int amount) const;
 private:
  int provisions_;
  std::pair<int, int> troops_;
};
} // namespace domain::models
#endif //DOMAIN_INCLUDE_MODELS_VILLAGE_H

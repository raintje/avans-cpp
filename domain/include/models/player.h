#ifndef DOMAIN_INCLUDE_MODELS_PLAYER_H
#define DOMAIN_INCLUDE_MODELS_PLAYER_H

constexpr int STARTING_GOLD = 100;
constexpr int STARTING_PROVISIONS = 10;

#include <map>

#include "random_wrapper.h"
#include "db_wrapper.h"
#include "tile_contents.h"

namespace domain::models {
class Player {
 public:
  explicit Player();
  ~Player();

  [[nodiscard]]int GetGold() const;
  void ReduceGoldBy(int gold);
  void IncreaseGoldBy(int gold);

  [[nodiscard]]int GetProvisions() const;
  void ReduceProvisionsBy(int provisions);
  void IncreaseProvisionsBy(int provisions);
  void Upkeep();

  [[nodiscard]]std::map<int, int> *GetWarband();
  void AddTroops(int id, int amount);
  void RemoveTroops(int id, int amount);

  [[nodiscard]]std::pair<int, int> GetProvince();
  void SetProvince(const std::pair<int, int> &province);

  [[nodiscard]]std::pair<int, int> GetLocation();
  void SetLocation(std::pair<int, int> location);

 private:
  std::pair<int, int> location_;
  std::pair<int, int> current_province_;
  std::map<int, int> warband_;
  int gold_;
  int provisions_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_PLAYER_H

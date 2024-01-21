#ifndef DOMAIN_INCLUDE_MODELS_KING_H
#define DOMAIN_INCLUDE_MODELS_KING_H

constexpr int KING_THREAT_LEVEL = 5;

#include <map>

#include "tile.h"
#include "db_wrapper.h"
#include "random_wrapper.h"
#include "tile_contents.h"

namespace domain::models {

class King {
 public:
  explicit King();
  ~King();

  [[nodiscard]]std::map<int, int> GetWarband();
  [[nodiscard]]std::pair<int, int> GetProvince();
  [[nodiscard]]std::pair<int, int> GetLocation();
  void SetLocation(std::pair<int, int> location);
 private:
  std::pair<int, int> location_;
  std::pair<int, int> province_;
  std::map<int, int> warband_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_KING_H

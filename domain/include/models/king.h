#ifndef DOMAIN_INCLUDE_MODELS_KING_H
#define DOMAIN_INCLUDE_MODELS_KING_H

constexpr int KING_THREAT_LEVEL = 5;

#include <unordered_map>

#include "tile.h"
#include "db_wrapper.h"
#include "random_wrapper.h"
#include "structs/location.h"

namespace domain::models {

class King : public Tile {
 public:
  explicit King(structs::Location location);

  [[nodiscard]]char GetDrawChar() const override;
 private:
  std::unordered_map<int, int> warband_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_KING_H

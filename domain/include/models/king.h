#ifndef DOMAIN_INCLUDE_MODELS_KING_H
#define DOMAIN_INCLUDE_MODELS_KING_H

#define KING_THREAT_LEVEL 5

#include <unordered_map>

#include "tile.h"
#include "db_wrapper.h"
#include "structs/location.h"

namespace domain::models {

class King : public Tile {
 public:
  King(structs::Location province, structs::Location position);

  [[nodiscard]]char GetDrawChar() const override;
  [[nodiscard]]structs::Location GetLocation() const override;
 private:
  std::unordered_map<int, int> warband_;
  structs::Location province_;
  structs::Location position_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_KING_H

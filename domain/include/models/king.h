#ifndef DOMAIN_INCLUDE_MODELS_KING_H
#define DOMAIN_INCLUDE_MODELS_KING_H

constexpr int KING_THREAT_LEVEL = 5;

#include <map>

#include "tile.h"
#include "db_wrapper.h"
#include "random_wrapper.h"
#include "tile_contents.h"

namespace domain::models {

class King : public TileContents {
 public:
  explicit King();
  ~King() override;
 private:
  std::map<int, int> warband_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_KING_H

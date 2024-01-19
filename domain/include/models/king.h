#ifndef DOMAIN_INCLUDE_MODELS_KING_H
#define DOMAIN_INCLUDE_MODELS_KING_H

constexpr int KING_THREAT_LEVEL = 5;

#include <map>

#include "tile.h"
#include "db_wrapper.h"
#include "random_wrapper.h"
#include "encounter.h"

namespace domain::models {

class King : public Encounter {
 public:
  explicit King();
  void Interact(models::Player player) override;
 private:
  std::map<int, int> warband_;
};

} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_KING_H

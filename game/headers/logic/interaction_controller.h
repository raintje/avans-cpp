#ifndef GAME_HEADERS_LOGIC_INTERACTION_CONTROLLER_H
#define GAME_HEADERS_LOGIC_INTERACTION_CONTROLLER_H

#include "logger.h"
#include "validation.h"

#include "drawing/hud.h"

#include "models/player.h"
#include "models/village.h"
#include "models/tile.h"
#include "models/city.h"
#include "models/enemy.h"
#include "models/king.h"
#include "models/province.h"
#include "models/land.h"

namespace game::logic {
class InteractionController {
 public:
  explicit InteractionController();
  ~InteractionController();

  void SetLogger(const std::shared_ptr<util::Logger> &logger);

  void HandleVillageInteraction(domain::models::Player *p, int turn_counter, domain::models::Tile *t);
  void HandleCityInteraction(domain::models::Player *p, int turn_counter, domain::models::Tile *t);
  [[nodiscard]]static int HandleEnemyInteraction(domain::models::Enemy *e);
  [[nodiscard]]bool HandleKingInteraction(domain::models::King *k, domain::models::Land *l);

 private:
  std::shared_ptr<util::Logger> logger_;
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_INTERACTION_CONTROLLER_H

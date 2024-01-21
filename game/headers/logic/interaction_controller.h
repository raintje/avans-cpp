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

namespace game::logic {
class InteractionController {
 public:
  InteractionController();
  ~InteractionController();

  void HandleVillageInteraction(domain::models::Player *p, util::Logger *l, int turn_counter, domain::models::Tile *t);
  void HandleCityInteraction(domain::models::Player *p, util::Logger *l, int turn_counter, domain::models::Tile *t);
  void HandleEnemyInteraction(domain::models::Enemy *e);
};
} // namespace game::logic

#endif //GAME_HEADERS_LOGIC_INTERACTION_CONTROLLER_H

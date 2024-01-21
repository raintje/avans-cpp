#ifndef GAME_HEADERS_DRAWING_DOMAIN_H
#define GAME_HEADERS_DRAWING_DOMAIN_H

#include <iostream>

#include "models/land.h"

namespace game::drawing {

class DomainDrawer {
 public:
  DomainDrawer();
  ~DomainDrawer();

  void DrawLand(domain::models::Land *land, std::pair<int, int> selected_province);
  void DrawProvince(domain::models::Province *province);
  void DrawWarband(std::map<int, int> *warband);
  void DrawCityInteraction();
  void DrawVillageInteraction();
};

} // namespace game::drawing::domain

#endif //GAME_HEADERS_DRAWING_DOMAIN_H

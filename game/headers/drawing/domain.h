#ifndef GAME_HEADERS_DRAWING_DOMAIN_H
#define GAME_HEADERS_DRAWING_DOMAIN_H

#include <iostream>

#include "models/land.h"

namespace game::drawing {

class DomainDrawer {
 public:
  DomainDrawer();
  ~DomainDrawer();

  static void DrawLand(domain::models::Land *land, std::pair<int, int> selected_province);
  static void DrawProvince(domain::models::Province *province);
  static void DrawWarband(const std::map<int, int> &warband);
};

} // namespace game::drawing::domain

#endif //GAME_HEADERS_DRAWING_DOMAIN_H

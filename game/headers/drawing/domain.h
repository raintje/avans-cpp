#ifndef GAME_HEADERS_DRAWING_DOMAIN_H
#define GAME_HEADERS_DRAWING_DOMAIN_H

#include <iostream>

#include "models/land.h"

namespace game::drawing {

static void DrawLand(domain::models::Land *land, std::pair<int, int> selected_province);
static void DrawProvince(domain::models::Province *province);
static void DrawWarband(std::map<int, int> *warband);
static void DrawCityInteraction(domain::models::City *city);
static void DrawVillageInteraction(domain::models::Village *village);

} // namespace game::drawing::domain

#endif //GAME_HEADERS_DRAWING_DOMAIN_H

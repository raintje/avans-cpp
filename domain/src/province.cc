#include "models/province.h"

namespace domain::models {
Province::Province(std::pair<int, int> location, structs::ProvinceStatistics province_statistics) :
    location_(std::move(location)),
    faction_(util::RandomWrapper::GetInstance()->RandomItemFromVector(
        db::DbWrapper::GetInstance()->GetFactions())) {
  for (int x = 0; x < PROVINCE_SIZE; ++x) {
    for (int y = 0; y < PROVINCE_SIZE; ++y) {
      auto new_loc = std::make_pair(x, y);
      tiles_.push_back(std::move(std::make_unique<Tile>(enums::EMPTY, new_loc)));
    }
  }
  GenerateProvince(province_statistics);
  GenerateEnemies();
}
Province::~Province() = default;

std::pair<int, int> Province::GetLocation() const { return location_; }
Tile *Province::GetTileByLocation(std::pair<int, int> location) const {
  auto it = std::find_if(tiles_.begin(),
                         tiles_.end(),
                         [&location](const std::unique_ptr<Tile> &obj) { return obj->GetLocation() == location; });
  if (it == tiles_.end()) return nullptr;
  return tiles_[std::distance(tiles_.begin(), it)].get();
}

void Province::GenerateMountain(std::pair<int, int> location) const {
  auto center = GetTileByLocation(location);
  center->SetType(enums::MOUNTAIN);

  auto left = std::make_pair(location.first - 1, location.second);
  if (left.first >= 0) {
    auto t = GetTileByLocation(left);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto right = std::make_pair(location.first + 1, location.second);
  if (right.first < PROVINCE_SIZE) {
    auto t = GetTileByLocation(right);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto up = std::make_pair(location.first, location.second - 1);
  if (up.second >= 0) {
    auto t = GetTileByLocation(up);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto down = std::make_pair(location.first, location.second + 1);
  if (down.second < PROVINCE_SIZE) {
    auto t = GetTileByLocation(down);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto up_left = std::make_pair(location.first - 1, location.second - 1);
  if (up_left.first >= 0 && up_left.second >= 0) {
    auto t = GetTileByLocation(up_left);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto up_right = std::make_pair(location.first + 1, location.second - 1);
  if (up_right.first < PROVINCE_SIZE && up_right.second >= 0) {
    auto t = GetTileByLocation(up_right);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto down_left = std::make_pair(location.first - 1, location.second + 1);
  if (down_left.first >= 0 && down_left.second < PROVINCE_SIZE) {
    auto t = GetTileByLocation(down_left);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }

  auto down_right = std::make_pair(location.first + 1, location.second + 1);
  if (down_right.first < PROVINCE_SIZE && down_right.second < PROVINCE_SIZE) {
    auto t = GetTileByLocation(down_right);
    if (t != nullptr) t->SetType(enums::MOUNTAIN);
  }
}

void Province::GenerateEnemies() {
  for (int i = 0; i < util::RandomWrapper::GetInstance()->RandomIntInRange(1, 3); ++i) {
    bool enemy_generated = false;
    while (!enemy_generated) {
      auto ran_loc = std::make_pair(
          util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE - 1),
          util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE - 1)
      );

      auto t = GetTileByLocation(ran_loc);

      if (t != nullptr && t->GetType() == enums::EMPTY) {
        int threatLevel = util::RandomWrapper::GetInstance()->RandomIntInRange(0, 4);

        t->SetEncounter(std::move(std::make_unique<Enemy>(faction_, threatLevel)));
        t->SetType(enums::ENEMY);

        enemy_generated = true;
      }
    }
  }
}

void Province::GenerateProvince(structs::ProvinceStatistics province_statistics) {
  for (int i = 0; i < province_statistics.num_mountains; ++i) {
    auto ran_loc = std::make_pair(util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE),
                                  util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE));
    GenerateMountain(ran_loc);
  }

  for (int i = 0; i < province_statistics.num_cities; ++i) {
    bool city_generated = false;
    while (!city_generated) {
      auto ran_loc = std::make_pair(util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE),
                                    util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE));

      auto t = GetTileByLocation(ran_loc);

      if (t != nullptr && t->GetType() == enums::EMPTY) {
        t->SetType(enums::CITY);
        t->SetEncounter(std::move(std::make_unique<City>()));
        city_generated = true;
      }
    }
  }

  for (int i = 0; i < province_statistics.num_villages; ++i) {
    bool village_generated = false;
    while (!village_generated) {
      auto ran_loc = std::make_pair(util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE),
                                    util::RandomWrapper::GetInstance()->RandomIntInRange(0, PROVINCE_SIZE));

      auto t = GetTileByLocation(ran_loc);

      if (t != nullptr && t->GetType() == enums::EMPTY) {
        t->SetType(enums::VILLAGE);
        t->SetEncounter(std::move(std::make_unique<Village>()));
        village_generated = true;
      }
    }
  }
}

} // namespace domain::models
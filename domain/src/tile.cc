#include "models/tile.h"

namespace domain::models {

Tile::Tile(enums::TileType type, std::pair<int, int> location) :
    type_(type),
    location_(std::move(location)),
    encounter_(nullptr) {}

Tile::~Tile() = default;

char Tile::GetDrawChar() const {
  switch (type_) {
    case enums::KING:return '$';
    case enums::ENEMY:return '*';
    case enums::MOUNTAIN:return '^';
    case enums::VILLAGE:return '@';
    case enums::CITY:return 'O';
    case enums::PLAYER: return 'K';
    default:return '~';
  }
}

void Tile::SetEncounter(std::unique_ptr<models::Encounter> encounter) {
  if (encounter_ != nullptr) encounter_ = nullptr;
  encounter_ = std::move(encounter);
}

void Tile::SetType(enums::TileType type) { type_ = type; }
enums::TileType Tile::GetType() { return type_; }
std::pair<int, int> Tile::GetLocation() const { return location_; }

} // namespace domain::models

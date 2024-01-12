#include "models/tile.h"

namespace domain::models {

Tile::Tile(const structs::Location &location, const enums::TileType &tile_type)
    : location_(location),
      tile_type_(tile_type) {}

Tile::~Tile() = default;

structs::Location Tile::GetLocation() const { return location_; }

char Tile::GetDrawChar() const {
  switch (tile_type_) {
    case enums::MOUNTAIN:return '^';
    case enums::VILLAGE:return '@';
    case enums::CITY:return 'O';
    case enums::EMPTY:return '~';
    case enums::WARBAND:return '*';
    case enums::PLAYER:return 'K';
  }
  return -1;
}

} // namespace domain::models

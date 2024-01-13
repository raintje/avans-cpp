#include "models/tile.h"

namespace domain::models {

Tile::Tile(structs::Location location) :
    location_(location) {}
Tile::~Tile() = default;

structs::Location Tile::GetLocation() const { return location_; }
char Tile::GetDrawChar() const { return '~'; }

} // namespace domain::models

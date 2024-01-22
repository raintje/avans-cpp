#include "models/tile.h"

namespace domain::models {

Tile::Tile(enums::TileType type, std::pair<int, int> location) :
    type_(type),
    location_(std::move(location)),
    contents_(nullptr) {}

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

void Tile::SetTileContents(std::unique_ptr<models::TileContents> encounter) {
  if (contents_ != nullptr) contents_ = nullptr;
  contents_ = std::move(encounter);
}

void Tile::SetType(enums::TileType type) { type_ = type; }
enums::TileType Tile::GetType() { return type_; }
std::pair<int, int> Tile::GetLocation() const { return location_; }
TileContents *Tile::GetTileContents() { return contents_.get(); }
std::unique_ptr<TileContents> Tile::MoveContents() { return std::move(contents_); }

} // namespace domain::models

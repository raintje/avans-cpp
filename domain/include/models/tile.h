#ifndef DOMAIN_INCLUDE_MODELS_TILE_H
#define DOMAIN_INCLUDE_MODELS_TILE_H

#include <memory>

#include "enums/tile_type.h"
#include "tile_contents.h"

namespace domain::models {
class Tile {
 public:
  Tile(enums::TileType type, std::pair<int, int> location);
  ~Tile();

  void SetTileContents(std::unique_ptr<models::TileContents> encounter);
  void SetType(enums::TileType type);

  [[nodiscard]]TileContents *GetTileContents();
  [[nodiscard]]std::unique_ptr<TileContents> MoveContents();
  [[nodiscard]]enums::TileType GetType();
  [[nodiscard]]char GetDrawChar() const;
  [[nodiscard]]std::pair<int, int> GetLocation() const;
 private:
  std::unique_ptr<TileContents> contents_;
  std::pair<int, int> location_;
  enums::TileType type_;
};
} // namespace domain::models

#endif //DOMAIN_INCLUDE_MODELS_TILE_H

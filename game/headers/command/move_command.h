#ifndef GAME_HEADERS_COMMAND_MOVE_COMMAND_H
#define GAME_HEADERS_COMMAND_MOVE_COMMAND_H

#include <map>
#include <iostream>

#include "command.h"
#include "models/tile.h"
#include "models/province.h"

namespace game::command {

class MoveCommand : public Command {
 public:
  MoveCommand();
  void Execute() override;
  void PrintAvailableOptions() override;
 private:
  std::map<std::string, domain::models::Tile *> neighbours_;
};

} // namespace game::command

#endif //GAME_HEADERS_COMMAND_MOVE_COMMAND_H

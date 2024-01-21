#ifndef GAME_HEADERS_COMMAND_COMMAND_H
#define GAME_HEADERS_COMMAND_COMMAND_H

namespace game::command {

class Command {
 public:
  virtual void Execute() = 0;
  virtual void PrintAvailableOptions() = 0;
};

} // namespace game::command

#endif //GAME_HEADERS_COMMAND_COMMAND_H

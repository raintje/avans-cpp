#include "drawing/logic.h"

namespace game::drawing {

static bool PrintBattlePrompt(bool first_turn) {
  if (first_turn) std::cout << "Je bent een vijandige krijgsbende tegengekomen! Wat wil je doen?" << std::endl;
  std::cout << "1. Vechten" << std::endl;
  std::cout << "2. Terugtrekken" << std::endl;
  std::string input;

  while (input != "1" || input != "2") {
    std::cout << "Voer hier je antwoord in (1, 2): ";
    std::getline(std::cin, input);
  }

  return input == "1";
}

} // namespace game::drawing

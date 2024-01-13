#include "../headers/state/game.h"

int main() {
  auto g = new game::state::Game();

  g->RunGame();

  delete g;
}

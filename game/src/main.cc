#include <iostream>

#include "../headers/state/game.h"

using namespace game;

int main() {
  auto g = new state::Game();

  g->RunGame();

  delete g;
}

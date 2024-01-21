#include "drawing/hud.h"

namespace game::drawing {

void HudDrawer::ClearConsole() { std::cout << "\x1B[2J\x1B[H"; }

} // namespace game::drawing

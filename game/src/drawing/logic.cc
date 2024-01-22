#include "drawing/logic.h"

namespace game::drawing {

LogicDrawer::LogicDrawer() = default;
LogicDrawer::~LogicDrawer() = default;

void LogicDrawer::PrintAttack(int round,
                              bool friendly,
                              const std::string &attacker_name,
                              const std::string &target_name,
                              bool hit) {
  std::string fr = friendly ? "Eigen" : "Vijandelijke";
  std::string fr2 = friendly ? "vijandelijke" : "jouw";
  std::string m = hit ? "raakt" : "mist";
  std::cout
      << "Ronde " + std::to_string(round) + ": " + fr + " " + attacker_name + " valt de " + fr2 + " " + target_name
          + " aan! Hij " + m + "!" << std::endl;
}

void LogicDrawer::PrintTroopDeath(int round, bool friendly, const std::string &troop_name) {
  std::string fr = friendly ? "Vijandelijke" : "Eigen";
  std::cout << "Ronde " + std::to_string(round) + ": " + fr + " " + troop_name + " is gesneuveld!" << std::endl;
}
} // namespace game::drawing

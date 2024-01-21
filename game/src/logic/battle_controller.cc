#include "logic/battle_controller.h"

namespace game::logic {

BattleController::BattleController() :
    battle_ongoing_(true),
    logic_drawer_(std::make_shared<drawing::LogicDrawer>()) {}
BattleController::~BattleController() = default;

void BattleController::Start(std::map<int, int> *player_warband, std::map<int, int> *enemy_warband) {
  while (battle_ongoing_)
    Round(*player_warband, *enemy_warband);
}

void BattleController::Round(const std::map<int, int> &player_warband, const std::map<int, int> &enemy_warband) {
  int volley = 1;

  while (volley < 5) {
    std::pair<int, int> player_losses;
    std::pair<int, int> enemy_losses;

    for (auto i : player_warband) {
      if (CheckTroopType(i.first, volley)) {
        int hits = 0;
        int target = FindTarget(enemy_warband);

        if (target == -1) break;
        for (int a = 0; a <= i.second; ++a) {
          if (Attack(i.first, target)) ++hits;
        }

        enemy_losses = {target, hits};
      }
    }

    for (auto i : enemy_warband) {
      if (CheckTroopType(i.first, volley)) {
        int hits = 0;
        int target = FindTarget(player_warband);

        if (target == -1) break;
        for (int a = 0; a <= i.second; ++a) {
          if (Attack(i.first, target)) ++hits;
        }

        player_losses = {target, hits};
      }
    }

    SubtractLosses(player_warband, player_losses);
    SubtractLosses(enemy_warband, enemy_losses);
    ++volley;
  }

  battle_ongoing_ = ConfirmDefeat(player_warband);
  battle_ongoing_ = ConfirmDefeat(enemy_warband);

}

void BattleController::Retreat(const std::map<int, int> &player_warband, const std::map<int, int> &enemy_warband) {
  int volley = 1;

  while (volley < 5) {
    std::pair<int, int> player_losses;

    for (auto i : enemy_warband) {
      if (CheckTroopType(i.first, volley)) {
        int hits = 0;
        int target = FindTarget(player_warband);

        if (target == -1) break;
        for (int a = 0; a <= i.second; ++a) {
          if (Attack(i.first, target)) ++hits;
        }

        player_losses = {target, hits};
      }
    }

    SubtractLosses(player_warband, player_losses);
    ++volley;
  }
}

bool BattleController::Attack(int attacker, int target) {
  auto chance = db::DbWrapper::GetInstance()->GetChanceToHit(attacker, target);
  return util::RandomWrapper::GetInstance()->PercentChance(chance);
}

bool BattleController::ConfirmDefeat(const std::map<int, int> &warband) {
  bool troops_alive = true;
  for (const auto &i : warband) {
    if (i.second > 0) troops_alive = false;
  }
  return troops_alive;
}

void BattleController::SubtractLosses(std::map<int, int> warband, const std::pair<int, int> &losses) {
  warband[losses.first] = warband[losses.first] - losses.second;
}

int BattleController::FindTarget(const std::map<int, int> &warband) {
  for (const auto &t : warband) {
    if (t.second > 0) return t.first;
  }
  return -1;
}

bool BattleController::CheckTroopType(int id, int volley) {
  auto types = db::DbWrapper::GetInstance()->GetTroopTypes();
  auto type = db::DbWrapper::GetInstance()->GetTroopTypeById(id);

  return type == types[volley - 1];
}

} // namespace game::logic

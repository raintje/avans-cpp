#include "logic/battle_controller.h"

namespace game::logic {

BattleController::BattleController() :
    god_mode_(false),
    round_(1),
    player_(nullptr),
    enemy_(nullptr) {}
BattleController::~BattleController() = default;

void BattleController::SetEnemy(domain::models::Enemy *enemy) { enemy_ = enemy; }
void BattleController::SetPlayer(domain::models::Player *player) { player_ = player; }

void BattleController::Start() {
  std::cout << "Het gevecht begint..." << std::endl;
  while (!ConfirmDefeat(*player_->GetWarband()) && !ConfirmDefeat(*enemy_->GetWarband())) {
    std::string input;
    std::cout << "Wil je vechten (1) of vluchten (2)?" << std::endl;
    while (!util::Validation::StringIsNumber(input)) {
      std::getline(std::cin, input);
    }

    auto i = std::stoi(input);
    if (i == 1) Round();
    else {
      Retreat();
      break;
    }
  }

  if (ConfirmDefeat(*enemy_->GetWarband())) {
    std::cout << "De vijand is verslagen, al zijn rijkdommen behoren nu tot jou." << std::endl;
    player_->IncreaseProvisionsBy(enemy_->GetProvisions());
    player_->IncreaseGoldBy(enemy_->GetGold());
  }
}

void BattleController::Round() {
  int volley = 1;

  while (volley < 5) {
    for (auto i : *player_->GetWarband()) {
      if (CheckTroopType(i.first, volley)) {
        int hits = 0;
        int target = FindTarget(*enemy_->GetWarband());

        if (target == -1) break;
        for (int a = 0; a <= i.second; ++a) {
          auto hit = Attack(i.first, target);
          drawing::LogicDrawer::PrintAttack(round_,
                                            true,
                                            std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(i.first)),
                                            std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(target)),
                                            hit);
          if (hit) {
            ++hits;
            drawing::LogicDrawer::PrintTroopDeath(round_,
                                                  true,
                                                  std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(target)));
          }
        }

        enemy_->RemoveTroops(target, hits);
      }
    }

    if (!god_mode_) {
      for (auto i : *enemy_->GetWarband()) {
        if (CheckTroopType(i.first, volley)) {
          int hits = 0;
          int target = FindTarget(*player_->GetWarband());

          if (target == -1) break;
          for (int a = 0; a <= i.second; ++a) {
            auto hit = Attack(i.first, target);
            drawing::LogicDrawer::PrintAttack(round_,
                                              false,
                                              std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(i.first)),
                                              std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(target)),
                                              hit);

            if (hit) {
              ++hits;
              drawing::LogicDrawer::PrintTroopDeath(round_,
                                                    false,
                                                    std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(target)));
            }
          }
          player_->RemoveTroops(target, hits);
        }
      }
    }

    ++volley;
  }

  ++round_;
}

void BattleController::Retreat() {
  if (!god_mode_) {
    std::cout << "Je probeert te vluchten, maar de vijand krijgt nog 1 ronde aan aanvallen op je!" << std::endl;
    int volley = 1;

    for (auto i : *enemy_->GetWarband()) {
      if (CheckTroopType(i.first, volley)) {
        int hits = 0;
        int target = FindTarget(*player_->GetWarband());

        if (target == -1) break;
        for (int a = 0; a <= i.second; ++a) {
          auto hit = Attack(i.first, target);
          drawing::LogicDrawer::PrintAttack(round_,
                                            false,
                                            std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(i.first)),
                                            std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(target)),
                                            hit);

          if (hit) {
            ++hits;
            drawing::LogicDrawer::PrintTroopDeath(round_,
                                                  false,
                                                  std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(target)));
          }
        }

        player_->RemoveTroops(target, hits);
      }
    }
  }
}

bool BattleController::Attack(int attacker, int target) {
  auto chance = db::DbWrapper::GetInstance()->GetChanceToHit(attacker, target);
  auto roll = util::RandomWrapper::GetInstance()->RandomIntInRange(0, 100);
  std::string missed = roll > chance ? "raakte" : "miste";
  logger_->WriteLine(
      "Ronde " + std::to_string(round_) + ": Manschap met ID " + std::to_string(attacker) + " valt manschap met ID "
          + std::to_string(target)
          + " aan, met een " + std::to_string(chance) + "% kans om te raken. Hij " + missed
          + " met een rol van " + std::to_string(roll) + ".");
  return roll > chance;
}

bool BattleController::ConfirmDefeat(const std::map<int, int> &warband) {
  return warband.empty();
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

void BattleController::SetLogger(const std::shared_ptr<util::Logger> &logger) { logger_ = logger; }

void BattleController::Reset() {
  round_ = 1;
  enemy_ = nullptr;
  player_ = nullptr;
}

void BattleController::ToggleGodMode() { god_mode_ = !god_mode_; }

} // namespace game::logic

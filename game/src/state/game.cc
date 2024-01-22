#include "state/game.h"

namespace game::state {

Game::Game() :
    running_(true),
    turn_counter_(1),
    player_(std::make_unique<domain::models::Player>()),
    state_(enums::SHOWING_LAND),
    land_(std::make_unique<domain::models::Land>()),
    selected_province_({0, 0}),
    logger_(std::make_shared<util::Logger>()),
    movement_controller_(std::make_unique<logic::MovementController>()),
    interaction_controller_(std::make_unique<logic::InteractionController>()),
    battle_controller_(std::make_unique<logic::BattleController>()) {
  movement_controller_->SetLogger(logger_);
  interaction_controller_->SetLogger(logger_);
  battle_controller_->SetLogger(logger_);
}
Game::~Game() = default;

void Game::ChangeLand() {
  drawing::DomainDrawer::DrawLand(land_.get(), selected_province_);
  std::cout << "Weet je zeker dat je van land wil wisselen? (Y/N): ";

  std::string input;
  std::getline(std::cin, input);
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);

  if (input == "y") {
    land_ = std::make_unique<domain::models::Land>();
    selected_province_ = {0, 0};
    logger_->WriteLine("Beurt " + std::to_string(turn_counter_++) + ": Speler is naar een ander land gegaan.");
  }
}

void Game::RunGame() {
  while (running_) {
    drawing::HudDrawer::ClearConsole();

    if (GetState() == enums::SHOWING_LAND) drawing::DomainDrawer::DrawLand(land_.get(), selected_province_);
    if (GetState() == enums::SHOWING_PROVINCE) drawing::DomainDrawer::DrawProvince(land_->GetCurrentProvince());
    if (GetState() == enums::SHOWING_WARBAND) {
      drawing::DomainDrawer::DrawWarband(*player_->GetWarband());
      std::cout << "Goud: " << player_->GetGold() << std::endl;
      std::cout << "Proviand: " << player_->GetProvisions() << std::endl;
    }

    for (const auto &s : CompileAvailableCommands()) {
      std::cout << s << std::endl;
    }

    std::cout << "Voer een commando uit:  ";

    std::string input;
    std::getline(std::cin, input);
    HandleCommand(input);
    CheckVictoryConditions();
  }
}

void Game::HandleCommand(std::string command) {
  auto i = std::move(command);
  std::transform(i.begin(), i.end(), i.begin(), ::tolower);

  if (i == "stop") {
    logger_->WriteLine("Beurt " + std::to_string(turn_counter_) + ": Speler heeft het spel gesloten.");
    running_ = false;
  }
  if (i == "m") SetState(enums::SHOWING_LAND);
  if (i == "b") SetState(enums::SHOWING_WARBAND);
  if (i == "p" && land_->GetCurrentProvince() != nullptr) SetState(enums::SHOWING_PROVINCE);

  if (i == "c" && GetState() == enums::SHOWING_LAND) {
    turn_counter_++;
    if (!god_mode_)
      player_->Upkeep();
    ChangeLand();
  }

  if (i == "q" && GetState() == enums::SHOWING_PROVINCE) {
    if (!god_mode_) player_->Upkeep();
    movement_controller_->MoveAllEnemies(land_->GetCurrentProvince());
    logger_->WriteLine("Ronde " + std::to_string(turn_counter_++) + ": Speler heeft zijn beurt overgeslagen.");
    return;
  }

  if (i == "god") {
    god_mode_ = !god_mode_;
    battle_controller_->ToggleGodMode();
  }

  if (i == "rosebud") {
    player_->IncreaseGoldBy(10000);
    player_->IncreaseProvisionsBy(10000);
  }

  if (i == "romeo") {
    player_->ReduceGoldBy(player_->GetGold());
    player_->ReduceProvisionsBy(player_->GetProvisions());
  }

  if (movement_controller_->CheckIfMovementCommand(i)) {
    if (GetState() == enums::SHOWING_LAND && land_->GetCurrentProvince() == nullptr) {
      auto temp = selected_province_;
      ChangeSelectedProvince(i);
      logger_->WriteLine("Beurt " + std::to_string(turn_counter_++) + ": Speler heeft de geselecteerde provincie van ["
                             + std::to_string(temp.first) + ", " + std::to_string(temp.second) + "] naar ["
                             + std::to_string(selected_province_.first) + ", "
                             + std::to_string(selected_province_.second) + "] veranderd.");
    }

    if (GetState() == enums::SHOWING_PROVINCE) {
      MoveToAdjacentProvince(i);
      auto next_loc = movement_controller_->PrepareNextLocation(i, player_.get());
      auto t = land_->GetCurrentProvince()->GetTileByLocation(next_loc);
      if (t->GetType() == domain::enums::EMPTY) {
        movement_controller_->MovePlayer(player_.get(),
                                         land_->GetCurrentProvince(),
                                         turn_counter_++,
                                         next_loc);
        movement_controller_->MoveAllEnemies(land_->GetCurrentProvince());
        if (!god_mode_) player_->Upkeep();
      } else {
        if (t->GetType() == domain::enums::VILLAGE) {
          interaction_controller_->HandleVillageInteraction(player_.get(), turn_counter_++, t);
          movement_controller_->MoveAllEnemies(land_->GetCurrentProvince());
          if (!god_mode_) player_->Upkeep();
        }

        if (t->GetType() == domain::enums::CITY) {
          interaction_controller_->HandleCityInteraction(player_.get(), turn_counter_++, t);
          movement_controller_->MoveAllEnemies(land_->GetCurrentProvince());
          if (!god_mode_) player_->Upkeep();
        }

        if (t->GetType() == domain::enums::ENEMY) {
          auto e = reinterpret_cast<domain::models::Enemy *>(t->GetTileContents());
          auto interaction = interaction_controller_->HandleEnemyInteraction(e);
          battle_controller_->SetPlayer(player_.get());
          battle_controller_->SetEnemy(e);

          if (interaction == 1) {
            battle_controller_->Start();
            ++turn_counter_;
            std::string confirmation;
            while (confirmation != "ok") {
              std::cout << "Type \"ok\" om door te gaan..." << std::endl;
              std::getline(std::cin, confirmation);
            }
          }

          if (interaction == 2) {
            drawing::DomainDrawer::DrawWarband(*e->GetWarband());
            std::string confirmation;
            while (confirmation != "ok") {
              std::cout << "Type \"ok\" om door te gaan..." << std::endl;
              std::getline(std::cin, confirmation);
            }
          } else {
            battle_controller_->Retreat();
          }

          battle_controller_->Reset();
          t->SetType(domain::enums::EMPTY);
          t->SetTileContents(nullptr);
          movement_controller_->MoveAllEnemies(land_->GetCurrentProvince());
          if (!god_mode_) player_->Upkeep();
        }

        if (t->GetType() == domain::enums::KING) {
          std::cout << "Hoera! De koning is gesneuveld!" << std::endl;
          logger_->WriteLine("Beurt " + std::to_string(turn_counter_) + ": De speler heeft het spel gewonnen.");
          running_ = interaction_controller_->HandleKingInteraction(land_->GetKing()->get(), land_.get());
        }
      }
    }
  }

  if (i == "g" && GetState() == enums::SHOWING_LAND && land_->GetCurrentProvince() == nullptr) {
    land_->EnterProvince(selected_province_, player_.get());
    SetState(enums::SHOWING_PROVINCE);
    logger_->WriteLine("Beurt " +
        std::to_string(turn_counter_++) + ": Speler heeft provincie op locatie ["
                           + std::to_string(selected_province_.first) + ", "
                           + std::to_string(selected_province_.second) + "] betreedt.");
  }
}

std::vector<std::string> Game::CompileAvailableCommands() {
  std::vector<std::string> result;

  std::string show_warband = "b - inspecteer je eigen krijgsbende";
  std::string show_province = "p - toon de huidige provincie";
  std::string show_land = "m - toon de kaart van het huidige land";
  std::string pass_turn = "q - doe niets";

  if (GetState() == enums::SHOWING_WARBAND) {
    result.emplace_back(std::move(show_land));
    if (land_->GetCurrentProvince() != nullptr) result.emplace_back(std::move(show_province));
  }

  if (GetState() == enums::SHOWING_PROVINCE) {
    result.emplace_back(std::move(show_warband));
    result.emplace_back(std::move(show_land));
    result.emplace_back(std::move(pass_turn));
    auto v = movement_controller_->CheckViableMoves(land_->GetCurrentProvince(), player_->GetLocation());
    for (auto r : v) {
      result.emplace_back(std::move(r));
    }

    auto t = CheckForInteractableTiles();

    if (t.contains("up"))
      result.emplace_back("w - benader de tegel ten noorde van je.");
    if (t.contains("down"))
      result.emplace_back("s - benader de tegel ten zuide van je.");
    if (t.contains("left"))
      result.emplace_back("a - benader de tegel ten westen van je.");
    if (t.contains("right"))
      result.emplace_back("d - benader de tegel ten oosten van je.");
  }

  if (GetState() == enums::SHOWING_LAND) {
    if (land_->GetCurrentProvince() != nullptr) {
      result.emplace_back(std::move(show_province));
    } else {
      result.emplace_back("wasd - verander selectie van provincie (binnenste provincies niet benaderbaar)");
    }

    result.emplace_back(std::move(show_warband));
    result.emplace_back("c - reis naar een ander land");
  }

  return result;
}

bool Game::CheckIfMiddleProvince(std::pair<int, int> new_location) {
  if (new_location == std::make_pair(1, 1)) return true;
  if (new_location == std::make_pair(1, 2)) return true;
  if (new_location == std::make_pair(2, 1)) return true;
  if (new_location == std::make_pair(2, 2)) return true;
  return false;
}

void Game::ChangeSelectedProvince(const std::string &command) {

  auto temp = selected_province_;

  if (command == "a") {
    if (temp.first - 1 >= 0)
      temp = {temp.first - 1, temp.second};
  }

  if (command == "d") {
    if (temp.first + 1 < LAND_SIZE)
      temp = {temp.first + 1, temp.second};
  }

  if (command == "w") {
    if (temp.second - 1 >= 0)
      temp = {temp.first, temp.second - 1};
  }

  if (command == "s") {
    if (temp.second + 1 < LAND_SIZE)
      temp = {temp.first, temp.second + 1};
  }

  if (!CheckIfMiddleProvince(temp)) {
    selected_province_ = std::move(temp);
  }

}

std::map<std::string, domain::models::Tile *> Game::CheckForInteractableTiles() {
  std::map<std::string, domain::models::Tile *> result;
  auto temp = player_->GetLocation();

  auto left = std::make_pair(temp.first - 1, temp.second);
  if (left.first >= 0) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(left);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("left", t);
  }

  auto right = std::make_pair(temp.first + 1, temp.second);
  if (right.first < PROVINCE_SIZE) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(right);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("right", t);
  }

  auto up = std::make_pair(temp.first, temp.second - 1);
  if (up.second >= 0) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(up);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("up", t);
  }

  auto down = std::make_pair(temp.first, temp.second + 1);
  if (down.second < PROVINCE_SIZE) {
    auto t = land_->GetCurrentProvince()->GetTileByLocation(down);

    if (t->GetType() != domain::enums::EMPTY && t->GetType() != domain::enums::MOUNTAIN)
      result.emplace("down", t);
  }

  return result;
}

void Game::CheckVictoryConditions() {
  if (player_->GetWarband()->empty()) {
    std::cout << "Helaas! Al je troepen zijn gesneuveld!" << std::endl;
    running_ = false;
    logger_->WriteLine("Beurt " + std::to_string(turn_counter_) + ": De speler heeft het spel verloren.");
  }
}

enums::GameState Game::GetState() { return state_; }
void Game::SetState(enums::GameState state) { state_ = state; }

void Game::MoveToAdjacentProvince(const std::string &command) {
  auto l = land_->GetCurrentProvince()->GetLocation();
  auto p = player_->GetLocation();

  if (command == "a") {
    if (p.first - 1 < 0) {
      if (l.first - 1 >= 0) {
        selected_province_ = std::make_pair(l.first - 1, l.second);
        land_->EnterProvince(selected_province_, player_.get());
        land_->GetCurrentProvince()->GetTileByLocation(player_->GetLocation())->SetType(domain::enums::EMPTY);
      }
    }
  }

  if (command == "d") {
    if (p.first + 1 >= PROVINCE_SIZE) {
      if (l.first + 1 < LAND_SIZE) {
        selected_province_ = std::make_pair(l.first + 1, l.second);
        land_->EnterProvince(selected_province_, player_.get());
        land_->GetCurrentProvince()->GetTileByLocation(player_->GetLocation())->SetType(domain::enums::EMPTY);
      }
    }
  }

  if (command == "w") {
    if (p.second - 1 < 0) {
      if (l.second - 1 >= 0) {
        selected_province_ = std::make_pair(l.first, l.second - 1);
        land_->EnterProvince(selected_province_, player_.get());
        land_->GetCurrentProvince()->GetTileByLocation(player_->GetLocation())->SetType(domain::enums::EMPTY);
      }
    }
  }

  if (command == "s") {
    if (p.second + 1 >= PROVINCE_SIZE) {
      if (l.second + 1 < LAND_SIZE) {
        selected_province_ = std::make_pair(l.first, l.second + 1);
        land_->EnterProvince(selected_province_, player_.get());
        land_->GetCurrentProvince()->GetTileByLocation(player_->GetLocation())->SetType(domain::enums::EMPTY);
      }
    }
  }
}

} // namespace game::state
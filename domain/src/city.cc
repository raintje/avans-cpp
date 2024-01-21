#include "models/city.h"

namespace domain::models {

City::City(const std::string &faction) {
  auto id = db::DbWrapper::GetInstance()->GetTroopIdByFaction(faction);
  troops_ = std::make_pair(id, util::RandomWrapper::GetInstance()->RandomIntInRange(MIN_TROOPS_CITY, MAX_TROOPS_CITY));
}

City::~City() = default;

int City::GetTroopId() const { return troops_.first; }
int City::GetTroopCount() const { return troops_.second; }

void City::BuyTroops(Player *p, int amount) const {
  if (troops_.second - amount < 0) {
    std::cout << "De stad heeft niet genoeg troepen om aan je aanvraag te voldoen." << std::endl;
  } else if (troops_.second <= 0) {
    std::cout << "Er zijn geen manschappen meer over in deze stad." << std::endl;
  } else {
    auto data = db::DbWrapper::GetInstance()->GetTroopDataById(GetTroopId());
    auto price = std::get<4>(data);
    auto total = price * amount;

    if (total > p->GetGold()) {
      std::cout << "Niet voldoende goud om deze troepen te kopen!" << std::endl;
    } else {
      p->ReduceGoldBy(total);
      p->AddTroops(GetTroopId(), amount);
    }
  }
}

void City::BuyProvisions(Player *p, int amount) const {
  auto total = amount * PROVISION_PRICE_CITY;

  if (total > p->GetGold()) {
    std::cout << "Niet voldoende goud om zoveel proviand in te slaan!" << std::endl;
  } else {
    p->ReduceGoldBy(total);
    p->IncreaseProvisionsBy(amount);
  }
}

void City::Interact() {
  std::cout << "Je benadert de stad, wat zou je willen doen?" << std::endl;
  std::cout << "1. Manschappen rekruteren." << std::endl;
  std::cout << "2. Proviand inslaan." << std::endl;
  std::cout << "3. De stad verlaten." << std::endl;
  std::cout << "Type hier je keuze (1, 2, 3): " << std::endl;
}
}

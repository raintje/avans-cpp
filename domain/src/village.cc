#include "models/village.h"

namespace domain::models {
Village::Village(const std::string &faction) :
    provisions_(util::RandomWrapper::GetInstance()->RandomIntInRange(
        MIN_PROVISIONS_VILLAGE,
        MAX_PROVISIONS_VILLAGE)),
    troops_(
        std::make_pair(db::DbWrapper::GetInstance()->GetTroopIdByFaction(faction),
                       util::RandomWrapper::GetInstance()->RandomIntInRange(MIN_TROOPS_VILLAGE, MAX_TROOPS_VILLAGE))
    ) {}

Village::~Village() = default;

int Village::GetTroopId() const { return troops_.first; }

void Village::BuyTroops(domain::models::Player *p, int amount) const {
  if (troops_.second - amount < 0) {
    std::cout << "Het dorp bevat niet genoeg manschappen om aan je aanvraag te voldoen." << std::endl;
  } else if (troops_.second <= 0) {
    std::cout << "Er zijn geen troepen meer aanwezig in dit dorp." << std::endl;
  } else {
    auto data = db::DbWrapper::GetInstance()->GetTroopDataById(GetTroopId());
    auto price = std::get<4>(data);
    auto total = price * amount;

    if (total > p->GetGold()) {
      std::cout << "Niet voldoende goud om deze troepen te kopen!" << std::endl;
    } else {
      p->ReduceGoldBy(total);
      p->AddTroops(GetTroopId());
    }
  }
}

void Village::BuyProvisions(domain::models::Player *p, int amount) const {
  if (provisions_ - amount < 0) {
    std::cout << "Het dorp heeft niet genoeg proviand om aan je aanvraag te voldoen." << std::endl;
  } else if (provisions_ <= 0) {
    std::cout << "Er is geen proviand meer aanwezig in dit dorp." << std::endl;
  } else {
    auto total = amount * PROVISION_PRICE_VILLAGE;

    if (total > p->GetGold()) {
      std::cout << "Niet voldoende goud om zoveel proviand in te slaan!" << std::endl;
    } else {
      p->ReduceGoldBy(total);
      p->IncreaseProvisionsBy(amount);
    }
  }
}

} // namespace domain::models

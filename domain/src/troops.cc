#include "troops.h"

namespace domain {
Troops::Troops(std::string name,
               const std::string &type,
               Faction *faction,
               float price)
    : name_(std::move(name)), type_(STRING_TO_TROOPS_TYPE(type)), faction_(faction), price_(price) {}
Troops::~Troops() = default;

std::shared_ptr<Faction> Troops::GetFaction() const { return faction_; }
std::string Troops::GetName() const { return name_; }
TroopsType Troops::GetType() const { return type_; }
float Troops::GetPrice() const { return price_; }

} // namespace domain
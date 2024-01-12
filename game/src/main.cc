#include <iostream>
#include <tuple>

#include "db_wrapper.h"

int main() {
  auto f = db::DbWrapper::GetInstance()->GetFactions();

  for (const auto &fi : f) {
    auto id = db::DbWrapper::GetInstance()->GetTroopIdByFaction(fi);
    auto t = db::DbWrapper::GetInstance()->GetTroopDataById(id);

    std::cout
        << "ID: " << std::get<0>(t) << ", "
        << "Faction: " << std::get<1>(t) << ", "
        << "Sort: " << std::get<2>(t) << ", "
        << "Name: " << std::get<3>(t) << ", "
        << "Price: " << std::get<4>(t) << std::endl;
  }

}

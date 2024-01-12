#include <iostream>
#include <tuple>

#include "db_wrapper.h"

int main(int argc, char *argv[]) {
  auto f = db::DbWrapper::GetInstance()->GetTroopData(1);
  std::cout << "ID: " << std::get<0>(f)
            << ", Faction: " << std::get<1>(f)
            << ", Type: " << std::get<2>(f)
            << ", Name: " << std::get<3>(f)
            << ", Price: " << std::get<4>(f) << std::endl;
}

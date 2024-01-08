#ifndef DOMAIN_INCLUDE_PROVINCE_H
#define DOMAIN_INCLUDE_PROVINCE_H

#include <memory>
#include <vector>

#include "city.h"
#include "mountain.h"
#include "village.h"

namespace domain {

class Province {
 private:
  std::vector<std::unique_ptr<City>> cities_;
  std::vector<std::unique_ptr<Mountain>> mountains_;
  std::vector<std::unique_ptr<Village>> villages_;
};

} // domain

#endif //DOMAIN_INCLUDE_PROVINCE_H

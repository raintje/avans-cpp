#include "models/land.h"

namespace domain::models {

Land::Land() : current_province_(nullptr),
               king_(std::make_unique<King>()) {
  for (int y = 0; y < LAND_SIZE; ++y) {
    for (int x = 0; x < LAND_SIZE; ++x) {
      std::pair<int, int> loc = {x, y};
      structs::ProvinceStatistics stats = {
          util::RandomWrapper::GetInstance()->RandomIntInRange(0, MAX_CITIES),
          util::RandomWrapper::GetInstance()->RandomIntInRange(1, MAX_VILLAGES),
          util::RandomWrapper::GetInstance()->RandomIntInRange(0, MAX_MOUNTAINS)
      };
      province_statistics_[loc] = stats;
    }
  }
}

void Land::EnterProvince(const std::pair<int, int> location, Player *player) {
  if (current_province_ != nullptr) {
    current_province_->ClearEnemies();
    previous_provinces_.emplace(current_province_->GetLocation(),
                                std::move(current_province_));
  }

  if (previous_provinces_.contains(location)) {
    current_province_ = std::move(previous_provinces_[location]);
    current_province_->GenerateEnemies();
  } else current_province_ = std::make_unique<Province>(location, province_statistics_[location]);

  if (king_->GetProvince() == location) current_province_->GenerateKing(king_.get());
  current_province_->GeneratePlayer(player);
}

structs::ProvinceStatistics Land::GetProvinceStatistics(const int x, const int y) const {
  return province_statistics_.at({x, y});
}

models::Province *Land::GetCurrentProvince() const { return current_province_.get(); }

std::unique_ptr<King> *Land::GetKing() { return &king_; }
void Land::KillKing() { king_ = nullptr; }

Land::~Land() = default;

} // namespace domain::models
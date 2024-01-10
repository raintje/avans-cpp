#include "models/mountain.h"

namespace domain::models {
models::Mountain::Mountain(structs::Location location) : location_(location) {}
models::Mountain::~Mountain() = default;

[[nodiscard]]structs::Location models::Mountain::GetLocation() const { return location_; }

} // namespace domain::models

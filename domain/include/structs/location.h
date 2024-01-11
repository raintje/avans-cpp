#ifndef DOMAIN_INCLUDE_STRUCTS_LOCATION_H
#define DOMAIN_INCLUDE_STRUCTS_LOCATION_H

namespace domain::structs {
struct Location {
  int x;
  int y;

  bool operator==(const Location &l) const {
    return x == l.x && y == l.y;
  }

  bool operator!=(const Location &l) const {
    return x != l.x || y != l.y;
  }

  bool operator<(const Location &l) const {
    return x < l.x || y < l.y;
  }

  bool operator>(const Location &l) const {
    return x > l.x || (x == l.x && y > l.y);
  }

  Location operator/(int m) const {
    return {x / m, y / m};
  }
  Location operator*(int m) const {
    return {x * m, y * m};
  }

};
} // namespace domain::structs

#endif //DOMAIN_INCLUDE_STRUCTS_LOCATION_H

#include "CheckerPattern.hpp"

#include <cmath>

using std::floor;

Color CheckerPattern::color_at(const Point& point) const {
  int sum = static_cast<int>(floor(point.x)) +
            static_cast<int>(floor(point.y)) + static_cast<int>(floor(point.z));
  if (sum % 2 == 0) {
    return color_a;
  }
  return color_b;
}

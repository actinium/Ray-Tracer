#include "RingPattern.hpp"

#include <cmath>

using std::floor;
using std::sqrt;

Color RingPattern::color_at(const Point& point) const {
  int dist =
      static_cast<int>(floor(sqrt(point.x * point.x + point.z * point.z)));
  if (dist % 2 == 0) {
    return color_a;
  }
  return color_b;
}

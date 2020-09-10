#include "StripePattern.hpp"

#include <cmath>

using std::floor;

Color StripePattern::color_at(const Point& point) const {
  int x = static_cast<int>(floor(point.x));
  if (x % 2 == 0) {
    return color_a;
  }
  return color_b;
}

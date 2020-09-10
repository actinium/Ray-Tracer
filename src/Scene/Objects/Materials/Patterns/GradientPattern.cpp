#include "GradientPattern.hpp"

#include <cmath>

#include "Core/Math.hpp"

using std::floor;

Color GradientPattern::color_at(const Point& point) const {
  Color distance = color_b - color_a;
  double fraction = point.x - floor(point.x);
  return color_a + distance * fraction;
}

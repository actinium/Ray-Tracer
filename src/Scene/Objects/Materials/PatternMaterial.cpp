#include "PatternMaterial.hpp"

const Color& PatternMaterial::color_at(const Point& point) const {
  return pattern->color_at(point);
}

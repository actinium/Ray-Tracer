#include "PatternMaterial.hpp"

Color PatternMaterial::color_at_object(const Object* object,
                                       const Point& point) const {
  return pattern->color_at_object(object, point);
}

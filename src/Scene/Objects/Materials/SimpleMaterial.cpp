#include "SimpleMaterial.hpp"

Color SimpleMaterial::color_at_object(const Object*, const Point&) const {
  return color;
}

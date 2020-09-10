#include "Pattern.hpp"

#include "Core/Math.hpp"
#include "Scene/Objects/Object.hpp"

Color Pattern::color_at_object(const Object* object,
                               const Point& world_point) const {
  Point object_point = object->inverse_transform() * world_point;
  Point pattern_point = inverse_transform() * object_point;
  return color_at(pattern_point);
}

void Pattern::set_transform(const Matrix& matrix) {
  transform_ = matrix;
  inv_transform_ = inverse(matrix);
}

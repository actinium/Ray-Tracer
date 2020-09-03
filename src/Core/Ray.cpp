#include "Ray.hpp"

#include "Math.hpp"

Point Ray::position(double t) const { return origin + direction * t; }

Ray Ray::transform(const Matrix& matrix) const {
  return Ray(matrix * origin, matrix * direction);
}

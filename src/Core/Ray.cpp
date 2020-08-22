#include "Ray.hpp"

#include "Math.hpp"

Point position(const Ray& ray, double t) {
  return ray.origin + ray.direction * t;
}

Ray transform(const Ray& ray, const Matrix& matrix) {
  return Ray(matrix * ray.origin, matrix * ray.direction);
}

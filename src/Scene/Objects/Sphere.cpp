#include "Sphere.hpp"

#include <cmath>

#include "Core/Math.hpp"
#include "Core/Ray.hpp"

using std::sqrt;

Intersections Sphere::intersect(const Ray& ray) {
  Ray ray2 = ::transform(ray, inverse_transform());
  Intersections is;
  Vector sphere_to_ray = ray2.origin - Point(0, 0, 0);
  double a = dot(ray2.direction, ray2.direction);
  double b = 2 * dot(ray2.direction, sphere_to_ray);
  double c = dot(sphere_to_ray, sphere_to_ray) - 1;
  double discriminant = b * b - 4 * a * c;
  if (discriminant >= 0) {
    is.emplace_back((-b - sqrt(discriminant)) / (2 * a), this);
    is.emplace_back((-b + sqrt(discriminant)) / (2 * a), this);
  }
  return is;
}

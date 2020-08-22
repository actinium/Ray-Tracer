#include "Sphere.hpp"

#include <cmath>

#include "Core/Math.hpp"
#include "Core/Ray.hpp"

using std::sqrt;

Intersections Sphere::intersect(const Ray& ray) const {
  Ray ray2 = ::transform(ray, inverse_transform());
  Intersections is;
  Vector sphere_to_ray = ray2.origin - Point::Origin;
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

Vector Sphere::normal_at(const Point& world_point) const {
  const Point object_point = inverse_transform() * world_point;
  const Vector object_normal = object_point - Point::Origin;
  Vector world_normal = transpose(inverse_transform()) * object_normal;
  world_normal.w = 0;
  return normalize(world_normal);
}

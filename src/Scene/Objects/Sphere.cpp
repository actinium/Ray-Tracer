#include "Sphere.hpp"

#include <cmath>

#include "Core/Math.hpp"
#include "Core/Ray.hpp"

using std::sqrt;

void Sphere::local_intersect(const Ray& ray, Intersections& is) const {
  Vector sphere_to_ray = ray.origin - Point::Origin;
  double a = dot(ray.direction, ray.direction);
  double b = 2 * dot(ray.direction, sphere_to_ray);
  double c = dot(sphere_to_ray, sphere_to_ray) - 1;
  double discriminant = b * b - 4 * a * c;
  if (discriminant >= 0) {
    is.emplace_back((-b - sqrt(discriminant)) / (2 * a), this);
    is.emplace_back((-b + sqrt(discriminant)) / (2 * a), this);
  }
}

Vector Sphere::local_normal_at(const Point& point) const {
  return Vector(point.x, point.y, point.z);
}

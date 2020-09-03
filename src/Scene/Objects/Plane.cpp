#include "Plane.hpp"

#include <cmath>

#include "Core/Constants.hpp"

using std::abs;

Intersections Plane::local_intersect(const Ray& ray) const {
  Intersections is;
  if (abs(ray.direction.y) < EPSILON) {
    return is;
  }
  double t = -ray.origin.y / ray.direction.y;
  is.emplace_back(t, this);
  return is;
}

Vector Plane::local_normal_at(const Point&) const { return Vector(0, 1, 0); }

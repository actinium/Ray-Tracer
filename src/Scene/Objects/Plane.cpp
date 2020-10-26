#include "Plane.hpp"

#include <cmath>

#include "Core/Constants.hpp"

using std::abs;

void Plane::local_intersect(const Ray& ray, Intersections& is) const {
  if (abs(ray.direction.y) < EPSILON) {
    return;
  }
  double t = -ray.origin.y / ray.direction.y;
  is.emplace_back(t, this);
}

Vector Plane::local_normal_at(const Point&) const { return Vector(0, 1, 0); }

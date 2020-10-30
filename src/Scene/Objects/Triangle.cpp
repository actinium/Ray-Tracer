#include "Triangle.hpp"

#include <cmath>

#include "Core/Constants.hpp"

using std::abs;

Intersections Triangle::local_intersect(const Ray& ray) const {
  Vector dir_cross_e2 = cross(ray.direction, e2);
  double det = dot(e1, dir_cross_e2);
  if (abs(det) < EPSILON) {
    return {};
  }

  double f = 1.0 / det;
  Vector p1_to_origin = ray.origin - p1;
  double u = f * dot(p1_to_origin, dir_cross_e2);
  if (u < 0 || u > 1) {
    return {};
  }

  Vector origin_cross_e1 = cross(p1_to_origin, e1);
  double v = f * dot(ray.direction, origin_cross_e1);
  if (v < 0 || (u + v) > 1) {
    return {};
  }

  double t = f * dot(e2, origin_cross_e1);
  return {Intersection(t, this)};
}

Vector Triangle::local_normal_at(const Point&) const { return normal; }

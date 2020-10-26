#include "Cylinder.hpp"

#include <cmath>
#include <utility>

#include "Core/Constants.hpp"

using std::abs;
using std::sqrt;
using std::swap;

namespace {
// Checks to see if the intersection at `t` is within a radius
// of 1 (the radius of the cylinder) from the y axis.
bool check_cap(const Ray& ray, double t) {
  double x = ray.origin.x + t * ray.direction.x;
  double z = ray.origin.z + t * ray.direction.z;

  return (x * x + z * z) <= 1;
}

void intersect_caps(const Cylinder& cyl, const Ray& ray, Intersections& xs) {
  // caps only matter if the cylinder is closed, and might possibly be
  // intersected by the ray.
  if (!cyl.is_closed || abs(ray.direction.y) < EPSILON) {
    return;
  }

  // check for an intersection with the lower end cap by intersecting
  // the ray with the plane at y=cyl.minimum
  double t = (cyl.minimum - ray.origin.y) / ray.direction.y;
  if (check_cap(ray, t)) {
    xs.emplace_back(t, &cyl);
  }

  // check for an intersection with the upper end cap by intersecting
  // the ray with the plane at y=cyl.maximum
  t = (cyl.maximum - ray.origin.y) / ray.direction.y;
  if (check_cap(ray, t)) {
    xs.emplace_back(t, &cyl);
  }
}
}  // namespace

void Cylinder::local_intersect(const Ray& ray, Intersections& xs) const {
  intersect_caps(*this, ray, xs);

  double a =
      ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;

  // ray is parallel to the y axis
  if (abs(a) < EPSILON) {
    return;
  }

  double b =
      2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
  double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
  double disc = b * b - 4 * a * c;

  // ray does not intersect the cylinder
  if (disc < 0) {
    return;
  }

  double t0 = (-b - sqrt(disc)) / (2 * a);
  double t1 = (-b + sqrt(disc)) / (2 * a);
  if (t0 > t1) swap(t0, t1);

  double y0 = ray.origin.y + t0 * ray.direction.y;
  if (minimum < y0 && y0 < maximum) {
    xs.emplace_back(t0, this);
  }

  double y1 = ray.origin.y + t1 * ray.direction.y;
  if (minimum < y1 && y1 < maximum) {
    xs.emplace_back(t1, this);
  }
}

Vector Cylinder::local_normal_at(const Point& point) const {
  double dist = point.x * point.x + point.z * point.z;

  if (dist < 1 && point.y >= maximum - EPSILON) {
    return Vector(0, 1, 0);
  }

  if (dist < 1 && point.y <= minimum + EPSILON) {
    return Vector(0, -1, 0);
  }

  return Vector(point.x, 0, point.z);
}

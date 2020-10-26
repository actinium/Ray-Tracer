#include "Cone.hpp"

#include <cmath>
#include <utility>

#include "Core/Constants.hpp"

using std::abs;
using std::sqrt;
using std::swap;

namespace {
// Checks to see if the intersection at `t` is within the radius of the cone
// from the y axis.
bool check_cap(const Ray& ray, double t, double radius) {
  double x = ray.origin.x + t * ray.direction.x;
  double z = ray.origin.z + t * ray.direction.z;

  return (x * x + z * z) <= (radius * radius);
}

void intersect_caps(const Cone& cone, const Ray& ray, Intersections& xs) {
  // caps only matter if the cone is closed, and might possibly be
  // intersected by the ray.
  if (!cone.is_closed || abs(ray.direction.y) < EPSILON) {
    return;
  }

  // check for an intersection with the lower end cap by intersecting
  // the ray with the plane at y=cone.minimum
  double t = (cone.minimum - ray.origin.y) / ray.direction.y;
  if (check_cap(ray, t, abs(cone.minimum))) {
    xs.emplace_back(t, &cone);
  }

  // check for an intersection with the upper end cap by intersecting
  // the ray with the plane at y=cone.maximum
  t = (cone.maximum - ray.origin.y) / ray.direction.y;
  if (check_cap(ray, t, abs(cone.maximum))) {
    xs.emplace_back(t, &cone);
  }
}
}  // namespace

void Cone::local_intersect(const Ray& ray, Intersections& xs) const {
  intersect_caps(*this, ray, xs);

  double a = ray.direction.x * ray.direction.x -
             ray.direction.y * ray.direction.y +
             ray.direction.z * ray.direction.z;
  double b = 2 * ray.origin.x * ray.direction.x -
             2 * ray.origin.y * ray.direction.y +
             2 * ray.origin.z * ray.direction.z;
  double c = ray.origin.x * ray.origin.x - ray.origin.y * ray.origin.y +
             ray.origin.z * ray.origin.z;

  // ray is parallel to one of the cone’s halves
  if (abs(a) < EPSILON) {
    double t = -c / (2 * b);
    xs.emplace_back(t, this);
    return;
  }

  double disc = b * b - 4 * a * c;

  // ray does not intersect the cone
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

Vector Cone::local_normal_at(const Point& point) const {
  double dist = point.x * point.x + point.z * point.z;

  if (dist < maximum * maximum && point.y >= maximum - EPSILON) {
    return Vector(0, 1, 0);
  }

  if (dist < minimum * minimum && point.y <= minimum + EPSILON) {
    return Vector(0, -1, 0);
  }

  double y = sqrt(point.x * point.x + point.z * point.z);
  if (point.y > 0) {
    y = -y;
  }

  return Vector(point.x, y, point.z);
}

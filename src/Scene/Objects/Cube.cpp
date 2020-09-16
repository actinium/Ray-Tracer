#include "Cube.hpp"

#include <algorithm>
#include <cmath>
#include <tuple>
#include <utility>

#include "Core/Constants.hpp"

using std::abs;
using std::max;
using std::min;
using std::pair;
using std::tie;

namespace {
pair<double, double> check_axis(double origin, double direction) {
  double tmin, tmax;
  double tmin_numerator = -1 - origin;
  double tmax_numerator = 1 - origin;

  if (abs(direction) >= EPSILON) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * INFINITY;
    tmax = tmax_numerator * INFINITY;
  }

  if (tmin > tmax) {
    double tmp = tmin;
    tmin = tmax;
    tmax = tmp;
  }

  return pair(tmin, tmax);
}
}  // namespace

Intersections Cube::local_intersect(const Ray& ray) const {
  double xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;

  tie(xtmin, xtmax) = check_axis(ray.origin.x, ray.direction.x);
  tie(ytmin, ytmax) = check_axis(ray.origin.y, ray.direction.y);
  tie(ztmin, ztmax) = check_axis(ray.origin.z, ray.direction.z);

  double tmin = max({xtmin, ytmin, ztmin});
  double tmax = min({xtmax, ytmax, ztmax});

  if (tmin > tmax) {
    return {};
  }
  return {Intersection(tmin, this), Intersection(tmax, this)};
}

Vector Cube::local_normal_at(const Point& point) const {
  double maxc = max({abs(point.x), abs(point.y), abs(point.z)});

  if (maxc == abs(point.x)) {
    return Vector(point.x, 0, 0);
  } else if (maxc == abs(point.y)) {
    return Vector(0, point.y, 0);
  }

  return Vector(0, 0, point.z);
}

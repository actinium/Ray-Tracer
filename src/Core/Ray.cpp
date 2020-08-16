#include "Ray.hpp"

#include "Math.hpp"

Point position(const Ray& ray, double t) {
  return ray.origin + ray.direction * t;
}

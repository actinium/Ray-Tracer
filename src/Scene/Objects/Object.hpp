#pragma once

#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"

class Object {
 public:
  virtual Intersections intersect(const Ray& ray) = 0;
};

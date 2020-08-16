#pragma once

#include "Core/Intersection.hpp"
#include "Object.hpp"

class Sphere : public Object {
 public:
  constexpr Sphere();

 public:
  Intersections intersect(const Ray& ray) override;
};

constexpr Sphere::Sphere() {}

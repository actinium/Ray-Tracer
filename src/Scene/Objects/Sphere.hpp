#pragma once

#include "Core/Intersection.hpp"
#include "Object.hpp"

class Sphere : public Object {
 public:
  constexpr Sphere() noexcept;

 public:
  Intersections intersect(const Ray& ray) const override;
  Vector normal_at(const Point& world_point) const override;
};

constexpr Sphere::Sphere() noexcept : Object() {}

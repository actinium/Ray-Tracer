#pragma once

#include "Scene/Objects/Object.hpp"

class Cylinder : public Object {
 public:
  constexpr Cylinder() noexcept;
  Cylinder(const Matrix& transform, const Material& material) noexcept;

 private:
  Intersections local_intersect(const Ray& ray) const override;
  Vector local_normal_at(const Point& point) const override;
};

constexpr Cylinder::Cylinder() noexcept : Object() {}

inline Cylinder::Cylinder(const Matrix& t, const Material& m) noexcept
    : Object(t, m) {}

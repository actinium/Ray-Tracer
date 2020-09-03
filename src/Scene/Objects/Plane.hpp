#pragma once

#include "Object.hpp"

class Plane : public Object {
 public:
  constexpr Plane() noexcept;
  Plane(const Matrix& transform, const Material& material) noexcept;

 private:
  Intersections local_intersect(const Ray& ray) const override;
  Vector local_normal_at(const Point& point) const override;
};

constexpr Plane::Plane() noexcept : Object() {}

inline Plane::Plane(const Matrix& t, const Material& m) noexcept
    : Object(t, m) {}

#pragma once

#include "Scene/Objects/Object.hpp"

class Cube : public Object {
 public:
  constexpr Cube() noexcept;
  Cube(const Matrix& transform, const Material& material) noexcept;

 private:
  Intersections local_intersect(const Ray& ray) const override;
  Vector local_normal_at(const Point& point) const override;
};

constexpr Cube::Cube() noexcept : Object() {}

inline Cube::Cube(const Matrix& t, const Material& m) noexcept : Object(t, m) {}

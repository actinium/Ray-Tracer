#pragma once

#include "Scene/Objects/Object.hpp"

class Sphere : public Object {
 public:
  constexpr Sphere() noexcept;
  Sphere(const Matrix& transform, const Material& material) noexcept;

 private:
  void local_intersect(const Ray& ray, Intersections& intersections) const override;
  Vector local_normal_at(const Point& point) const override;
};

constexpr Sphere::Sphere() noexcept : Object() {}

inline Sphere::Sphere(const Matrix& t, const Material& m) noexcept
    : Object(t, m) {}

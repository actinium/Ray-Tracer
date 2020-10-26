#pragma once

#include "Core/Constants.hpp"
#include "Scene/Objects/Object.hpp"

class Cylinder : public Object {
 public:
  constexpr Cylinder() noexcept;
  Cylinder(const Matrix& transform, const Material& material) noexcept;

 private:
  void local_intersect(const Ray& ray, Intersections& intersections) const override;
  Vector local_normal_at(const Point& point) const override;

 public:
  double minimum;
  double maximum;
  bool is_closed;
};

constexpr Cylinder::Cylinder() noexcept
    : Object(), minimum(NEG_INF), maximum(INF), is_closed(false) {}

inline Cylinder::Cylinder(const Matrix& t, const Material& m) noexcept
    : Object(t, m), minimum(NEG_INF), maximum(INF), is_closed(false) {}

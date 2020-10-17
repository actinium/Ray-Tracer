#pragma once

#include "Core/Constants.hpp"
#include "Scene/Objects/Object.hpp"

class Cone : public Object {
 public:
  constexpr Cone() noexcept;
  Cone(const Matrix& transform, const Material& material) noexcept;

 private:
  Intersections local_intersect(const Ray& ray) const override;
  Vector local_normal_at(const Point& point) const override;

 public:
  double minimum;
  double maximum;
  bool is_closed;
};

constexpr Cone::Cone() noexcept
    : Object(), minimum(NEG_INF), maximum(INF), is_closed(false) {}

inline Cone::Cone(const Matrix& t, const Material& m) noexcept
    : Object(t, m), minimum(NEG_INF), maximum(INF), is_closed(false) {}

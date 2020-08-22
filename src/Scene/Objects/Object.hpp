#pragma once

#include "Core/Intersection.hpp"
#include "Core/Matrix.hpp"
#include "Core/Ray.hpp"

class Object {
 public:
  constexpr Object() noexcept;

 public:
  virtual Intersections intersect(const Ray& ray) const = 0;
  virtual Vector normal_at(const Point& world_point) const = 0;

 public:
  const Matrix& transform() const;
  const Matrix& inverse_transform() const;
  void set_transform(const Matrix& matrix);

 private:
  Matrix transform_;
  Matrix inv_transform_;
};

constexpr Object::Object() noexcept
    : transform_{Matrix::Identity}, inv_transform_{Matrix::Identity} {}

inline const Matrix& Object::transform() const { return transform_; }
inline const Matrix& Object::inverse_transform() const {
  return inv_transform_;
}

#pragma once

#include "Core/Color.hpp"
#include "Core/Matrix.hpp"
#include "Core/Point.hpp"

class Object;

class Pattern {
 public:
  constexpr Pattern() noexcept;

 public:
  virtual Color color_at(const Point& point) const = 0;
  Color color_at_object(const Object* object, const Point& point) const;

 public:
  const Matrix& transform() const;
  const Matrix& inverse_transform() const;
  void set_transform(const Matrix& matrix);

 private:
  Matrix transform_;
  Matrix inv_transform_;
};

constexpr Pattern::Pattern() noexcept
    : transform_(Matrix::Identity), inv_transform_(Matrix::Identity) {}

inline const Matrix& Pattern::transform() const { return transform_; }
inline const Matrix& Pattern::inverse_transform() const {
  return inv_transform_;
}

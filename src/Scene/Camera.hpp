#pragma once

#include <cmath>
#include <cstddef>

#include "Core/Image.hpp"
#include "Core/Matrix.hpp"
#include "Core/Ray.hpp"
#include "Scene/Scene.hpp"

using std::tan;

class Camera {
 public:
  constexpr Camera(std::size_t width, std::size_t height,
                   double field_of_view) noexcept;

 public:
  const Matrix& transform() const;
  const Matrix& inverse_transform() const;
  void set_transform(const Matrix& matrix);
  void set_view_transform(const Point& from, const Point& to, const Vector& up);

  Ray ray_for_pixel(std::size_t x, std::size_t y) const;
  Image render(const Scene& scene) const;

 public:
  std::size_t width;
  std::size_t height;
  double aspect;
  double field_of_view;
  double half_width;
  double half_height;
  double pixel_size;

 private:
  Matrix transform_;
  Matrix inv_transform_;
};

constexpr Camera::Camera(std::size_t w, std::size_t h, double fov) noexcept
    : width(w),
      height(h),
      aspect(width / static_cast<double>(height)),
      field_of_view(fov),
      half_width(),
      half_height(),
      pixel_size(),
      transform_(Matrix::Identity),
      inv_transform_(Matrix::Identity) {
  double half_view = tan(field_of_view / 2);
  if (aspect >= 1) {
    half_width = half_view;
    half_height = half_view / aspect;
  } else {
    half_width = half_view * aspect;
    half_height = half_view;
  }
  pixel_size = (half_width * 2) / width;
}

inline const Matrix& Camera::transform() const { return transform_; }
inline const Matrix& Camera::inverse_transform() const {
  return inv_transform_;
}

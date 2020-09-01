#include "Camera.hpp"

#include "Core/Lighting.hpp"
#include "Core/Math.hpp"
#include "Core/Point.hpp"

void Camera::set_transform(const Matrix& matrix) {
  transform_ = matrix;
  inv_transform_ = inverse(matrix);
}

Ray Camera::ray_for_pixel(std::size_t x, std::size_t y) const {
  double xoffset = (x + 0.5) * pixel_size;
  double yoffset = (y + 0.5) * pixel_size;

  double world_x = half_width - xoffset;
  double world_y = half_height - yoffset;

  Point pixel = inverse_transform() * Point(world_x, world_y, -1);
  Point origin = inverse_transform() * Point(0, 0, 0);
  Vector direction = normalize(pixel - origin);
  return Ray(origin, direction);
}

Image Camera::render(const Scene& scene) const {
  Image image(width, height);
  for (std::size_t y = 0; y < height; ++y) {
    for (std::size_t x = 0; x < width; ++x) {
      Ray ray = ray_for_pixel(x, y);
      Color color = color_at(scene, ray);
      image(x, y) = color;
    }
  }
  return image;
}

#include "Object.hpp"

#include "Core/Math.hpp"

void Object::set_transform(const Matrix& matrix) {
  transform_ = matrix;
  inv_transform_ = inverse(matrix);
}

void Object::set_material(const Material& m) { material_ = &m; }

Intersections Object::intersect(const Ray& ray) const {
  Ray local_ray = ray.transform(inverse_transform());
  return local_intersect(local_ray);
}

Vector Object::normal_at(const Point& world_point) const {
  Point local_point = inverse(transform()) * world_point;
  Vector local_normal = local_normal_at(local_point);
  Vector world_normal = transpose(inverse_transform()) * local_normal;
  world_normal.w = 0;
  return normalize(world_normal);
}

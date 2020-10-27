#include "Object.hpp"

#include "Core/Math.hpp"

void Object::set_transform(const Matrix& matrix) {
  transform_ = matrix;
  inv_transform_ = inverse(matrix);
}

void Object::set_material(const Material* m) { material_ = m; }

Intersections Object::intersect(const Ray& ray) const {
  Ray local_ray = ray.transform(inverse_transform());
  return local_intersect(local_ray);
}

Vector Object::normal_at(const Point& world_point) const {
  Point local_point = world_to_object(world_point);
  Vector local_normal = local_normal_at(local_point);
  return normal_to_world(local_normal);
}

const Object* Object::parent() const { return parent_; }

void Object::set_parent(const Object* p) { parent_ = p; }

Point Object::world_to_object(Point p) const {
  if (parent_ != nullptr) {
    p = parent_->world_to_object(p);
  }
  return inverse_transform() * p;
}

Vector Object::normal_to_world(Vector n) const {
  n = transpose(inverse_transform()) * n;
  n.w = 0;
  n = normalize(n);
  if (parent_ != nullptr) {
    n = parent_->normal_to_world(n);
  }
  return n;
}

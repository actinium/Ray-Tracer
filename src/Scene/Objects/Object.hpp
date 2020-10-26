#pragma once

#include "Core/Intersection.hpp"
#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/Ray.hpp"
#include "Scene/Objects/Materials/Material.hpp"

class Object {
 public:
  constexpr Object() noexcept;
  Object(const Matrix& transform, const Material& material) noexcept;

 public:
  const Matrix& transform() const;
  const Matrix& inverse_transform() const;
  void set_transform(const Matrix& matrix);

  const Material& material() const;
  void set_material(const Material* material);

 public:
  Intersections intersect(const Ray& ray) const;
  Vector normal_at(const Point& world_point) const;

 private:
  virtual Intersections local_intersect(const Ray& ray) const = 0;
  virtual Vector local_normal_at(const Point& point) const = 0;

 public:
  const Object* parent() const;
  void set_parent(const Object* parent);

 private:
  const Object* parent_;
  Matrix transform_;
  Matrix inv_transform_;
  const Material* material_;
};

constexpr Object::Object() noexcept
    : parent_{nullptr},
      transform_{Matrix::Identity},
      inv_transform_{Matrix::Identity},
      material_{&Material::Default} {}

inline Object::Object(const Matrix& t, const Material& m) noexcept
    : parent_{nullptr},
      transform_{t},
      inv_transform_{inverse(t)},
      material_{&m} {}

inline const Matrix& Object::transform() const { return transform_; }
inline const Matrix& Object::inverse_transform() const {
  return inv_transform_;
}

inline const Material& Object::material() const { return *material_; }

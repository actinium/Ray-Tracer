#pragma once

#include "Core/Color.hpp"
#include "Core/Point.hpp"

class Object;

class Material {
 public:
  constexpr Material() noexcept;
  constexpr Material(double ambient, double diffuse, double specular,
                     double shininess, double reflective) noexcept;

 public:
  virtual Color color_at_object(const Object* object,
                                const Point& point) const = 0;

 public:
  double ambient;
  double diffuse;
  double specular;
  double shininess;
  double reflective;

 public:
  static const Material& Default;
};

constexpr Material::Material() noexcept
    : ambient(0.1),
      diffuse(0.9),
      specular(0.9),
      shininess(200),
      reflective(0) {}

constexpr Material::Material(double amb, double dif, double spec, double shin,
                             double refl) noexcept
    : ambient(amb),
      diffuse(dif),
      specular(spec),
      shininess(shin),
      reflective(refl) {}

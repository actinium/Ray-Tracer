#pragma once

#include "Core/Color.hpp"
#include "Core/Point.hpp"

class Material {
 public:
  constexpr Material() noexcept;
  constexpr Material(double ambient, double diffuse, double specular,
                     double shininess) noexcept;

 public:
  virtual const Color& color_at(const Point& point) const = 0;

 public:
  double ambient;
  double diffuse;
  double specular;
  double shininess;

 public:
  static const Material& Default;
};

constexpr Material::Material() noexcept
    : ambient(0.1), diffuse(0.9), specular(0.9), shininess(200) {}

constexpr Material::Material(double amb, double dif, double spec,
                             double shin) noexcept
    : ambient(amb), diffuse(dif), specular(spec), shininess(shin) {}

#pragma once

#include "Core/Color.hpp"

class Material {
 public:
  constexpr Material() noexcept;
  constexpr Material(const Color& color, double ambient, double diffuse,
                     double specular, double shininess) noexcept;

 public:
  Color color;
  double ambient;
  double diffuse;
  double specular;
  double shininess;

 public:
  static const Material Default;
};

constexpr Material::Material() noexcept
    : color(1, 1, 1),
      ambient(0.1),
      diffuse(0.9),
      specular(0.9),
      shininess(200) {}

constexpr Material::Material(const Color& c, double amb, double dif,
                             double spec, double shin) noexcept
    : color(c), ambient(amb), diffuse(dif), specular(spec), shininess(shin) {}

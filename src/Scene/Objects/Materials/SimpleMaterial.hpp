#pragma once

#include "Scene/Objects/Materials/Material.hpp"

class SimpleMaterial : public Material {
 public:
  constexpr SimpleMaterial() noexcept;
  constexpr SimpleMaterial(const Color& color, double ambient, double diffuse,
                           double specular, double shininess) noexcept;

 public:
  Color color_at_object(const Object* object,
                        const Point& point) const override;

 public:
  Color color;
};

constexpr SimpleMaterial::SimpleMaterial() noexcept
    : Material(), color(1, 1, 1) {}

constexpr SimpleMaterial::SimpleMaterial(const Color& c, double amb, double dif,
                                         double spec, double shin) noexcept
    : Material(amb, dif, spec, shin), color(c) {}

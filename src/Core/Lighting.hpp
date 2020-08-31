#pragma once

#include "Core/Point.hpp"
#include "Core/PreparedComputations.hpp"
#include "Core/Vector.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/Material.hpp"
#include "Scene/Scene.hpp"

Color lighting(const Material& m, const Light& light, const Point& position,
               const Vector& eyev, const Vector& normalv);

Color shade_hit(const Scene& scene, const PreparedComputations& comps);

Color color_at(const Scene& scene, const Ray& ray);

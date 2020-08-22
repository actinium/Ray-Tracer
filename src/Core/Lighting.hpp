#pragma once

#include "Core/Point.hpp"
#include "Core/Vector.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/Material.hpp"

Color lighting(const Material& m, const Light& light, const Point& position,
               const Vector& eyev, const Vector& normalv);

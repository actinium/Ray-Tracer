#pragma once

#include <vector>

#include "Core/Constants.hpp"
#include "Core/Intersection.hpp"
#include "Core/Point.hpp"
#include "Core/Ray.hpp"
#include "Core/Vector.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/Material.hpp"
#include "Scene/Scene.hpp"

class Object;

struct PreparedComputations {
  double t;
  const Object* object;

  Point point;
  Point over_point;
  Point under_point;

  Vector eye_vector;
  Vector normal_vector;
  Vector reflect_vector;

  double n1 = 0;
  double n2 = 0;

  bool inside;
};

Color lighting(const Material& material, const Object* object,
               const Light& light, const Point& position, const Vector& eyev,
               const Vector& normalv, bool in_shadow);

Color shade_hit(const Scene& scene, const PreparedComputations& comps,
                int remaining = MAX_RECURSION);

bool is_shadowed(const Point& point, const Light& light, const Scene& scene);

Color color_at(const Scene& scene, const Ray& ray,
               int remaining = MAX_RECURSION);

Color reflected_color(const Scene& scene, const PreparedComputations& comps,
                      int remaining = MAX_RECURSION);

Color refracted_color(const Scene& scene, const PreparedComputations& comps,
                      int remaining = MAX_RECURSION);

double schlick(const PreparedComputations& comps);

PreparedComputations prepare_computations(const Intersection& i, const Ray& r,
                                          const Intersections& is);

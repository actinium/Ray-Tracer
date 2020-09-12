#include "Lighting.hpp"

#include <cmath>

#include "Core/Constants.hpp"
#include "Core/Math.hpp"
#include "Scene/Objects/Object.hpp"

using std::pow;

//------------------------------------------------------------------------------
// Lighting
//------------------------------------------------------------------------------
Color lighting(const Material& material, const Object* object,
               const Light& light, const Point& position, const Vector& eyev,
               const Vector& normalv, bool in_shadow) {
  Color effective_color =
      material.color_at_object(object, position) * light.intensity;
  Vector lightv = normalize(light.position - position);

  Color ambient = effective_color * material.ambient;
  Color diffuse(0, 0, 0);
  Color specular(0, 0, 0);

  if (in_shadow) {
    return ambient;
  }

  double light_dot_normal = dot(lightv, normalv);
  if (light_dot_normal >= 0) {
    diffuse = effective_color * material.diffuse * light_dot_normal;
    Vector reflectv = reflect(-lightv, normalv);
    double reflect_dot_eye = dot(reflectv, eyev);

    if (reflect_dot_eye <= 0) {
      specular = Color(0, 0, 0);
    } else {
      double factor = pow(reflect_dot_eye, material.shininess);
      specular = light.intensity * material.specular * factor;
    }
  }

  return ambient + diffuse + specular;
}

//------------------------------------------------------------------------------
// Shade Hit
//------------------------------------------------------------------------------
Color shade_hit(const Scene& scene, const PreparedComputations& comps,
                int remaining) {
  Color shade;
  for (const Light* light : scene.lights) {
    bool in_shadow = is_shadowed(comps.over_point, *light, scene);
    Color surface = lighting(comps.object->material(), comps.object, *light,
                             comps.over_point, comps.eye_vector,
                             comps.normal_vector, in_shadow);
    shade = shade + surface;
  }
  Color reflected = reflected_color(scene, comps, remaining);
  shade = shade + reflected;
  return shade;
}

//------------------------------------------------------------------------------
// Is Shadowed
//------------------------------------------------------------------------------
bool is_shadowed(const Point& point, const Light& light, const Scene& scene) {
  Vector v = light.position - point;
  double distance = magnitude(v);
  Vector direction = normalize(v);
  Ray r(point, direction);
  Intersections intersections = scene.intersect(r);
  Hit hit = get_first_hit(intersections);
  if (hit.has_value() && hit.value().t < distance) {
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
// Color at
//------------------------------------------------------------------------------
Color color_at(const Scene& scene, const Ray& ray, int remaining) {
  Intersections is = scene.intersect(ray);
  Hit hit = get_first_hit(is);
  if (!hit.has_value()) {
    return Color(0, 0, 0);
  }
  Intersection i = hit.value();
  PreparedComputations comps = prepare_computations(i, ray);
  Color c = shade_hit(scene, comps, remaining);
  return c;
}

//------------------------------------------------------------------------------
// Reflected Color
//------------------------------------------------------------------------------
Color reflected_color(const Scene& scene, const PreparedComputations& comps,
                      int remaining) {
  if (remaining <= 0) {
    return Color(0, 0, 0);
  }
  if (comps.object->material().reflective == 0) {
    return Color(0, 0, 0);
  }

  Ray reflect_ray(comps.over_point, comps.reflect_vector);
  Color color = color_at(scene, reflect_ray, remaining - 1);

  return color * comps.object->material().reflective;
}

//------------------------------------------------------------------------------
// Prepare Computations
//------------------------------------------------------------------------------
PreparedComputations prepare_computations(const Intersection& i, const Ray& r) {
  PreparedComputations comps;

  comps.t = i.t;
  comps.object = i.object;

  comps.point = r.position(i.t);
  comps.eye_vector = -r.direction;
  comps.normal_vector = comps.object->normal_at(comps.point);
  if (dot(comps.normal_vector, comps.eye_vector) < 0) {
    comps.inside = true;
    comps.normal_vector = -comps.normal_vector;
  } else {
    comps.inside = false;
  }
  comps.reflect_vector = reflect(r.direction, comps.normal_vector);
  comps.over_point = comps.point + comps.normal_vector * EPSILON;

  return comps;
}

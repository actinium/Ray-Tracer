#include "Lighting.hpp"

#include <cmath>

#include "Math.hpp"
#include "Scene/Objects/Object.hpp"

using std::pow;

Color lighting(const Material& material, const Light& light,
               const Point& position, const Vector& eyev, const Vector& normalv,
               bool in_shadow) {
  Color effective_color = material.color * light.intensity;
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

Color shade_hit(const Scene& scene, const PreparedComputations& comps) {
  Color shade;
  for (const Light* light : scene.lights) {
    bool in_shadow = is_shadowed(comps.over_point, *light, scene);
    Color c = lighting(comps.object->material(), *light, comps.over_point,
                       comps.eye_vector, comps.normal_vector, in_shadow);
    shade = shade + c;
  }
  return shade;
}

Color color_at(const Scene& scene, const Ray& ray) {
  Intersections is = scene.intersect(ray);
  Hit h = hit(is);
  if (!h.has_value()) {
    return Color(0, 0, 0);
  }
  Intersection i = h.value();
  PreparedComputations comps = prepare_computations(i, ray);
  Color c = shade_hit(scene, comps);
  return c;
}

bool is_shadowed(const Point& point, const Light& light, const Scene& scene) {
  Vector v = light.position - point;
  double distance = magnitude(v);
  Vector direction = normalize(v);
  Ray r(point, direction);
  Intersections intersections = scene.intersect(r);
  Hit h = hit(intersections);
  if (h.has_value() && h.value().t < distance) {
    return true;
  }
  return false;
}

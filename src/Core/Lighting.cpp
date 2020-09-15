#include "Lighting.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

#include "Core/Constants.hpp"
#include "Core/Math.hpp"
#include "Scene/Objects/Object.hpp"

using std::pow;
using std::sqrt;

void calc_refraction_indicies(PreparedComputations& comps,
                              const Intersection& i, const Intersections& is);

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
  Color surface;
  for (const Light* light : scene.lights) {
    bool in_shadow = is_shadowed(comps.over_point, *light, scene);
    Color surface_color = lighting(comps.object->material(), comps.object,
                                   *light, comps.over_point, comps.eye_vector,
                                   comps.normal_vector, in_shadow);
    surface = surface + surface_color;
  }

  Color reflected = reflected_color(scene, comps, remaining);
  Color refracted = refracted_color(scene, comps, remaining);

  const Material& material = comps.object->material();
  if (material.reflective > 0 && material.transparency > 0) {
    double reflectance = schlick(comps);
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  }
  return surface + reflected + refracted;
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
  PreparedComputations comps = prepare_computations(i, ray, is);
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
// Refracted Color
//------------------------------------------------------------------------------
Color refracted_color(const Scene& scene, const PreparedComputations& comps,
                      int remaining) {
  if (remaining <= 0) {
    return Color(0, 0, 0);
  }
  if (comps.object->material().transparency == 0) {
    return Color(0, 0, 0);
  }

  double n_ratio = comps.n1 / comps.n2;
  double cos_theta_i = dot(comps.eye_vector, comps.normal_vector);
  double sin2_theta_t = n_ratio * n_ratio * (1 - cos_theta_i * cos_theta_i);
  if (sin2_theta_t > 1) {
    return Color(0, 0, 0);
  }

  double cos_theta_t = sqrt(1.0 - sin2_theta_t);
  Vector direction =
      comps.normal_vector * (n_ratio * cos_theta_i - cos_theta_t) -
      comps.eye_vector * n_ratio;
  Ray refract_ray(comps.under_point, direction);
  Color color = color_at(scene, refract_ray, remaining - 1) *
                comps.object->material().transparency;
  return color;
}

//------------------------------------------------------------------------------
// Schlick
//------------------------------------------------------------------------------
double schlick(const PreparedComputations& comps) {
  double angle_cos = dot(comps.eye_vector, comps.normal_vector);
  if (comps.n1 > comps.n2) {
    double n = comps.n1 / comps.n2;
    double sin2_t = n * n * (1.0 - angle_cos * angle_cos);
    if (sin2_t > 1) {
      return 1.0;
    }
    angle_cos = sqrt(1.0 - sin2_t);
  }
  double r0 = pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);
  return r0 + (1 - r0) * pow(1 - angle_cos, 5);
}

//------------------------------------------------------------------------------
// Prepare Computations
//------------------------------------------------------------------------------
PreparedComputations prepare_computations(const Intersection& i, const Ray& r,
                                          const Intersections& is) {
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
  comps.under_point = comps.point - comps.normal_vector * EPSILON;

  calc_refraction_indicies(comps, i, is);

  return comps;
}

void calc_refraction_indicies(PreparedComputations& comps,
                              const Intersection& i_hit,
                              const Intersections& is) {
  using Containers = std::vector<const Object*>;
  using Iterator = Containers::iterator;

  Containers containers;

  for (const Intersection& i : is) {
    if (i.t == i_hit.t && i.object == i_hit.object) {
      if (containers.empty()) {
        comps.n1 = 1.0;
      } else {
        comps.n1 = containers.back()->material().refractive_index;
      }
    }

    Iterator pos = std::find(containers.begin(), containers.end(), i.object);
    if (pos != containers.end()) {
      containers.erase(pos);
    } else {
      containers.push_back(i.object);
    }

    if (i.t == i_hit.t && i.object == i_hit.object) {
      if (containers.empty()) {
        comps.n2 = 1.0;
      } else {
        comps.n2 = containers.back()->material().refractive_index;
      }
      return;
    }
  }
}

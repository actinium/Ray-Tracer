#include "Lighting.hpp"

#include <cmath>

#include "Math.hpp"

using std::pow;

Color lighting(const Material& material, const Light& light,
               const Point& position, const Vector& eyev,
               const Vector& normalv) {
  Color effective_color = material.color * light.intensity;
  Vector lightv = normalize(light.position - position);

  Color ambient = effective_color * material.ambient;
  Color diffuse(0, 0, 0);
  Color specular(0, 0, 0);

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

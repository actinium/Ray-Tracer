#include "SpheresOnSphere.hpp"

#include <cmath>

#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "Scene/Scene.hpp"

using std::cos;
using std::sin;
using std::sqrt;

void spheres_on_sphere() {
  Scene scene;

  //----------------------------------------------------------------------------
  // Spheres on a sphere
  //
  // Using the Fibonacci sphere algorithm
  //----------------------------------------------------------------------------
  Material sphere_material;
  sphere_material.color = Color::Turquoise;
  sphere_material.ambient = 0.4;
  sphere_material.diffuse = 0.8;
  sphere_material.specular = 0.75;
  sphere_material.shininess = 300;

  const int num_spheres = 200;
  const double num_spheres_min_one = static_cast<double>(num_spheres - 1);
  const double phi = PI * (3 - sqrt(5));

  for (int k = 0; k < num_spheres; ++k) {
    const double y = 1 - 2 * k / num_spheres_min_one;
    const double radius = sqrt(1 - y * y);
    const double theta = k * phi;

    const double x = cos(theta) * radius;
    const double z = sin(theta) * radius;

    Sphere* s = new Sphere();
    s->set_transform(scaling(3) * translation(x, y, z) * scaling(0.2));
    s->set_material(sphere_material);
    scene.objects.push_back(s);
  }

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-4, 6, -10), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1080, 1080, PI / 3);
  camera.set_view_transform(Point(0, 0, -10), Point(0, 0, 0), Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/extra-06-spheres-on-sphere.png");
}

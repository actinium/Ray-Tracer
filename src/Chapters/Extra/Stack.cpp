#include "Stack.hpp"

#include <cmath>

#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "Scene/Scene.hpp"
#include "SpheresOnSphere.hpp"

using std::cos;
using std::sin;
using std::sqrt;

void extra_stack() {
  Scene scene;

  //----------------------------------------------------------------------------
  // Spheres
  //----------------------------------------------------------------------------
  Material sphere_material;
  sphere_material.color = Color::Orange;
  sphere_material.ambient = 0.4;
  sphere_material.diffuse = 0.8;
  sphere_material.specular = 0.75;
  sphere_material.shininess = 300;

  const int num_spheres = 21;
  for (int k = 0; k < num_spheres; ++k) {
    Sphere* s = new Sphere();
    s->set_transform(translation(0, 0.1 * (k - (num_spheres / 2)), 0) *
                     rotation_y(k * PI / 32) * scaling(0.4, 0.2, 1));
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
  camera.set_view_transform(Point(0, 0, -3), Point(0, 0, 0), Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/extra-07-stack.png");
}

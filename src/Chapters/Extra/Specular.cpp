#include "Specular.hpp"

#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "Scene/Scene.hpp"

namespace {
Image render_sphere(double specular) {
  Scene scene;

  //----------------------------------------------------------------------------
  // Sphere
  //----------------------------------------------------------------------------
  SimpleMaterial sphere_material;
  sphere_material.color = Color::Blue;
  sphere_material.specular = specular;

  Sphere s;
  s.set_material(&sphere_material);
  s.set_transform(scaling(4));
  scene.objects.push_back(&s);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-10, 10, -10), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(200, 200, PI / 3);
  camera.set_view_transform(Point(0, 0, -10), Point(0, 0, 0), Vector(0, 1, 0));

  return camera.render(scene);
}
}  // namespace

void extra_specular() {
  Image grid(200 * 6, 200);

  std::size_t x = 0;
  for (double specular = 0; specular <= 1; specular += 0.2) {
    Image image = render_sphere(specular);
    grid.write(x, 0, image);
    x += 200;
  }

  grid.save_as_png("images/extra-04-specular.png");
}

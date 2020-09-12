#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/PatternMaterial.hpp"
#include "Scene/Objects/Materials/Patterns/CheckerPattern.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"

namespace {
void reflection_scene() {
  Scene scene;

  //----------------------------------------------------------------------------
  // Materials
  //----------------------------------------------------------------------------
  SimpleMaterial material_red;
  material_red.color = Color::Red;
  material_red.ambient = 0.3;
  material_red.diffuse = 0.7;
  material_red.specular = 0.3;

  SimpleMaterial material_orange;
  material_orange.color = Color::Orange;
  material_orange.ambient = 0.3;
  material_orange.diffuse = 0.7;
  material_orange.specular = 0.3;

  SimpleMaterial material_yellow;
  material_yellow.color = Color::Yellow;
  material_yellow.ambient = 0.3;
  material_yellow.diffuse = 0.7;
  material_yellow.specular = 0.3;

  SimpleMaterial material_green;
  material_green.color = Color::Green;
  material_green.ambient = 0.3;
  material_green.diffuse = 0.7;
  material_green.specular = 0.3;

  SimpleMaterial material_blue;
  material_blue.color = Color::Blue;
  material_blue.ambient = 0.3;
  material_blue.diffuse = 0.7;
  material_blue.specular = 0.3;

  //----------------------------------------------------------------------------
  // Floor
  //----------------------------------------------------------------------------
  Plane floor;
  PatternMaterial floor_material;
  CheckerPattern floor_pattern(Color::White, Color::Darkgrey);
  floor_material.pattern = &floor_pattern;
  floor_material.specular = 0;
  floor.set_material(&floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Reflective Sphere
  //----------------------------------------------------------------------------
  Sphere middle;
  middle.set_transform(translation(-0.35, 1, 0.5));
  SimpleMaterial middle_material;
  middle_material.color = Color::Black;
  middle_material.diffuse = 0.95;
  middle_material.specular = 0.95;
  middle_material.shininess = 200;
  middle_material.reflective = 0.8;
  middle.set_material(&middle_material);
  scene.objects.push_back(&middle);

  //----------------------------------------------------------------------------
  // Mini Spheres
  //----------------------------------------------------------------------------
  Sphere sphere1;
  sphere1.set_transform(translation(0.5, 0.2, -0.5) * scaling(0.2));
  sphere1.set_material(&material_blue);
  scene.objects.push_back(&sphere1);

  Sphere sphere2;
  sphere2.set_transform(translation(-1.5, 0.3, -0.75) * scaling(0.3));
  sphere2.set_material(&material_green);
  scene.objects.push_back(&sphere2);

  Sphere sphere3;
  sphere3.set_transform(translation(1.2, 0.3, 0.15) * scaling(0.3));
  sphere3.set_material(&material_red);
  scene.objects.push_back(&sphere3);

  Sphere sphere4;
  sphere4.set_transform(translation(-2.6, 0.27, 1) * scaling(0.27));
  sphere4.set_material(&material_yellow);
  scene.objects.push_back(&sphere4);

  Sphere sphere5;
  sphere5.set_transform(translation(0.9, 0.31, 2.5) * scaling(0.31));
  sphere5.set_material(&material_orange);
  scene.objects.push_back(&sphere5);

  Sphere sphere6;
  sphere6.set_transform(translation(-0.4, 0.26, -1.05) * scaling(0.26));
  sphere6.set_material(&material_orange);
  scene.objects.push_back(&sphere6);

  Sphere sphere7;
  sphere7.set_transform(translation(1.5, 0.2, 1.15) * scaling(0.2));
  sphere7.set_material(&material_green);
  scene.objects.push_back(&sphere7);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-6, 10, -6), Color(0.5, 0.5, 0.5));
  scene.lights.push_back(&light);

  Light light2(Point(6, 10, -6), Color(0.5, 0.5, 0.5));
  scene.lights.push_back(&light2);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 4);
  camera.set_view_transform(Point(2.5, 3, -4.3), Point(0, 0.9, 0),
                            Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-11-reflection.png");
}
}  // namespace

void chapter11() { reflection_scene(); }

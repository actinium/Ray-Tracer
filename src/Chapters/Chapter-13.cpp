#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Cone.hpp"
#include "Scene/Objects/Cube.hpp"
#include "Scene/Objects/Cylinder.hpp"
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
  CheckerPattern floor_pattern(Color::Lightgrey, Color::White);
  floor_material.pattern = &floor_pattern;
  floor_material.specular = 0;
  floor.set_material(&floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Reflective Cylinder
  //----------------------------------------------------------------------------
  Cylinder middle;
  middle.maximum = 1.5;
  middle.minimum = 0;
  middle.is_closed = true;
  middle.set_transform(scaling(0.5, 1, 0.5) * translation(-0.75, 0, 1.5));
  SimpleMaterial middle_material;
  middle_material.color = Color::Black;
  middle_material.diffuse = 0.95;
  middle_material.specular = 0.95;
  middle_material.shininess = 200;
  middle_material.reflective = 0.7;
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
  image.save_as_png("images/chapter-13-cylinder-reflection.png");
}

void cylinders_scene() {
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
  CheckerPattern floor_pattern(Color::Lightgrey, Color::White);
  floor_material.pattern = &floor_pattern;
  floor_material.specular = 0;
  floor.set_material(&floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Big Cylinder
  //----------------------------------------------------------------------------
  Cylinder middle;
  middle.maximum = 1;
  middle.minimum = -1;
  middle.set_transform(translation(-0.75, 0.75, 1.5) * rotation_y(-PI / 3) *
                       rotation_z(PI / 2) * scaling(0.75, 1, 0.75));
  SimpleMaterial middle_material;
  middle_material.color = Color::Lightgrey;
  middle_material.diffuse = 0.95;
  middle_material.specular = 0.95;
  middle_material.shininess = 200;
  middle.set_material(&middle_material);
  scene.objects.push_back(&middle);

  //----------------------------------------------------------------------------
  // Mini Spheres
  //----------------------------------------------------------------------------
  Cylinder shape1;
  shape1.minimum = -1;
  shape1.maximum = 1;
  shape1.is_closed = true;
  shape1.set_transform(translation(0.5, 0.2, -0.5) * scaling(0.2));
  shape1.set_material(&material_blue);
  scene.objects.push_back(&shape1);

  Cube shape2;
  shape2.set_transform(translation(-1.5, 0.3, -0.75) * rotation_y(PI / 5) *
                       scaling(0.3));
  shape2.set_material(&material_green);
  scene.objects.push_back(&shape2);

  Cube shape3;
  shape3.set_transform(translation(1.2, 0.3, 0.15) * rotation_y(PI / 3) *
                       scaling(0.3));
  shape3.set_material(&material_red);
  scene.objects.push_back(&shape3);

  Sphere sphere4;
  sphere4.set_transform(translation(-2.6, 0.27, 1) * scaling(0.27));
  sphere4.set_material(&material_yellow);
  scene.objects.push_back(&sphere4);

  Cylinder shape5;
  shape5.minimum = -1;
  shape5.maximum = 2;
  shape5.is_closed = true;
  shape5.set_transform(translation(0.9, 0.31, 2.5) * scaling(0.31));
  shape5.set_material(&material_orange);
  scene.objects.push_back(&shape5);

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
  image.save_as_png("images/chapter-13-cylinders.png");
}
}  // namespace

void cone_scene() {
  Scene scene;
  //----------------------------------------------------------------------------
  // Floor
  //----------------------------------------------------------------------------
  Plane floor;
  SimpleMaterial wall_floor_material;
  wall_floor_material.color = Color::Lightgrey;
  wall_floor_material.specular = 0;
  floor.set_material(&wall_floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Middle Cone
  //----------------------------------------------------------------------------
  Cone middle;
  middle.set_transform(rotation_y(0.5) * translation(-0.5, 0.4, 0.5) *
                       scaling(0.8));
  middle.minimum = -0.5;
  middle.maximum = 0.5;
  middle.is_closed = true;
  SimpleMaterial middle_material;
  middle_material.color = Color::Orange;
  middle_material.diffuse = 0.7;
  middle_material.specular = 0.3;
  middle.set_material(&middle_material);
  scene.objects.push_back(&middle);

  //----------------------------------------------------------------------------
  // Right Cone
  //----------------------------------------------------------------------------
  Cone right;
  right.set_transform(rotation_y(-0.2) * scaling(0.5, 2, 0.5) *
                      translation(1.5, 0.5, -0.5) * scaling(0.5));
  right.minimum = -1;
  right.maximum = 0;
  right.is_closed = true;
  SimpleMaterial right_material;
  right_material.color = Color::Red;
  right_material.diffuse = 0.7;
  right_material.specular = 0.3;
  right.set_material(&right_material);
  scene.objects.push_back(&right);

  //----------------------------------------------------------------------------
  // Left Cone
  //----------------------------------------------------------------------------
  Cone left;
  left.set_transform(scaling(0.5, 1.5, 0.5) * translation(-1.8, 0, -0.75) *
                     scaling(0.33));
  left.minimum = 0;
  left.maximum = 1.3;
  left.is_closed = true;
  SimpleMaterial left_material;
  left_material.color = Color::Yellow;
  left_material.diffuse = 0.7;
  left_material.specular = 0.3;
  left.set_material(&left_material);
  scene.objects.push_back(&left);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-8, 10, -11), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 4);
  camera.set_view_transform(Point(0, 1.5, -5), Point(0, 0.5, 0),
                            Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-13-cones.png");
}

void chapter13() {
  reflection_scene();
  cylinders_scene();
  cone_scene();
}

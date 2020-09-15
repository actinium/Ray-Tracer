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
  SimpleMaterial floor_material;
  floor_material.color = Color::Lightgrey;
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

void refraction_scene() {
  Scene scene;

  //----------------------------------------------------------------------------
  // Floor
  //----------------------------------------------------------------------------
  Plane floor;
  floor.set_transform(rotation_y(PI));
  PatternMaterial floor_material;
  CheckerPattern floor_pattern(Color(0.0, 0.0, 0.0), Color(0.75, 0.75, 0.75));
  floor_material.pattern = &floor_pattern;
  floor_material.ambient = 0.5;
  floor_material.diffuse = 0.4;
  floor_material.specular = 0.8;
  floor_material.reflective = 0.1;
  floor.set_material(&floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Ceiling
  //----------------------------------------------------------------------------
  Plane ceiling;
  ceiling.set_transform(translation(0, 5, 0));
  PatternMaterial ceiling_material;
  CheckerPattern ceiling_pattern(Color(0.85, 0.85, 0.85), Color(1.0, 1.0, 1.0));
  ceiling_pattern.set_transform(scaling(0.2));
  ceiling_material.pattern = &ceiling_pattern;
  ceiling_material.ambient = 0.5;
  ceiling_material.specular = 0;
  ceiling.set_material(&ceiling_material);
  scene.objects.push_back(&ceiling);

  //----------------------------------------------------------------------------
  // Wall Material
  //----------------------------------------------------------------------------
  PatternMaterial wall_material;
  CheckerPattern wall_pattern(Color(0.0, 0.0, 0.0), Color(0.75, 0.75, 0.75));
  wall_pattern.set_transform(scaling(0.5));
  wall_material.pattern = &wall_pattern;
  wall_material.specular = 0;

  //----------------------------------------------------------------------------
  // West wall
  //----------------------------------------------------------------------------
  Plane west_wall;
  west_wall.set_transform(translation(-5, 0, 0) * rotation_z(PI / 2) *
                          rotation_y(PI / 2));
  west_wall.set_material(&wall_material);
  scene.objects.push_back(&west_wall);

  //----------------------------------------------------------------------------
  // East wall
  //----------------------------------------------------------------------------
  Plane east_wall;
  east_wall.set_transform(translation(5, 0, 0) * rotation_z(PI / 2) *
                          rotation_y(PI / 2));
  east_wall.set_material(&wall_material);
  scene.objects.push_back(&east_wall);

  //----------------------------------------------------------------------------
  // North wall
  //----------------------------------------------------------------------------
  Plane north_wall;
  north_wall.set_transform(translation(0, 0, 5) * rotation_x(PI / 2));
  north_wall.set_material(&wall_material);
  scene.objects.push_back(&north_wall);

  //----------------------------------------------------------------------------
  // South wall
  //----------------------------------------------------------------------------
  Plane south_wall;
  south_wall.set_transform(translation(0, 0, -5) * rotation_x(PI / 2));
  south_wall.set_material(&wall_material);
  scene.objects.push_back(&south_wall);

  //----------------------------------------------------------------------------
  // Background balls
  //----------------------------------------------------------------------------
  Sphere ball_1;
  ball_1.set_transform(translation(4, 1, 4));
  SimpleMaterial ball_1_material;
  ball_1_material.color = Color(0.8, 0.1, 0.3);
  ball_1_material.specular = 0;
  ball_1.set_material(&ball_1_material);
  scene.objects.push_back(&ball_1);

  Sphere ball_2;
  ball_2.set_transform(translation(4.6, 0.4, 2.9) * scaling(0.4));
  SimpleMaterial ball_2_material;
  ball_2_material.color = Color(0.1, 0.8, 0.2);
  ball_2_material.shininess = 200;
  ball_2.set_material(&ball_2_material);
  scene.objects.push_back(&ball_2);

  Sphere ball_3;
  ball_3.set_transform(translation(2.6, 0.6, 4.4) * scaling(0.6));
  SimpleMaterial ball_3_material;
  ball_3_material.color = Color(0.2, 0.1, 0.8);
  ball_3_material.shininess = 10;
  ball_3_material.specular = 0.4;
  ball_3.set_material(&ball_3_material);
  scene.objects.push_back(&ball_3);

  //----------------------------------------------------------------------------
  // Glass ball
  //----------------------------------------------------------------------------
  Sphere glass_ball;
  glass_ball.set_transform(translation(0.25, 1, 0));
  SimpleMaterial glass_material;
  glass_material.color = Color(0.8, 0.8, 0.9);
  glass_material.ambient = 0;
  glass_material.diffuse = 0.2;
  glass_material.specular = 0.9;
  glass_material.shininess = 300;
  glass_material.transparency = 0.8;
  glass_material.refractive_index = 1.57;
  glass_ball.set_material(&glass_material);
  scene.objects.push_back(&glass_ball);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-4.9, 4.9, 1), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1080, 1080, 0.5);
  camera.set_view_transform(Point(-4.5, 0.85, -4), Point(0, 0.85, 0),
                            Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-11-refraction.png");
}
}  // namespace

void chapter11() {
  reflection_scene();
  refraction_scene();
}

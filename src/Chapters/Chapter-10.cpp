#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/PatternMaterial.hpp"
#include "Scene/Objects/Materials/Patterns/CheckerPattern.hpp"
#include "Scene/Objects/Materials/Patterns/GradientPattern.hpp"
#include "Scene/Objects/Materials/Patterns/RingPattern.hpp"
#include "Scene/Objects/Materials/Patterns/StripePattern.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"

void chapter10() {
  Scene scene;
  //----------------------------------------------------------------------------
  // Floor
  //----------------------------------------------------------------------------
  Plane floor;
  PatternMaterial floor_material;
  CheckerPattern floor_pattern(Color::Orange, Color::White);
  floor_material.pattern = &floor_pattern;
  floor_material.specular = 0;
  floor.set_material(&floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Back Wall
  //----------------------------------------------------------------------------
  Plane wall;
  wall.set_transform(translation(0, 0, 5) * rotation_x(PI / 2));
  PatternMaterial wall_material;
  StripePattern wall_pattern(Color::Lightgrey, Color::White);
  wall_material.pattern = &wall_pattern;
  wall_material.diffuse = 0.8;
  wall_material.specular = 0;
  wall.set_material(&wall_material);
  scene.objects.push_back(&wall);

  //----------------------------------------------------------------------------
  // Middle Sphere
  //----------------------------------------------------------------------------
  Sphere middle;
  middle.set_transform(scaling(1, 0.3, 1) * translation(-0.1, 1, 0.5));
  GradientPattern middle_pattern(Color::Yellow, Color::Purple);
  middle_pattern.set_transform(scaling(2) * rotation_z(PI / 2) *
                               translation(0.5, 0, 0));
  PatternMaterial middle_material(&middle_pattern);
  middle_material.diffuse = 0.7;
  middle_material.specular = 0.3;
  middle_material.shininess = 30;
  middle.set_material(&middle_material);
  scene.objects.push_back(&middle);

  //----------------------------------------------------------------------------
  // Right Sphere
  //----------------------------------------------------------------------------
  Sphere right;
  right.set_transform(translation(1.5, 0.5, -0.5) * scaling(0.5, 1, 0.5) *
                      scaling(0.5));
  StripePattern right_pattern(Color::Red, Color::White);
  right_pattern.set_transform(scaling(0.3) * rotation_z(PI / 4));
  PatternMaterial right_material(&right_pattern);
  right_material.ambient = 0.3;
  right_material.diffuse = 0.7;
  right_material.specular = 0.3;
  right_material.shininess = 30;
  right.set_material(&right_material);
  scene.objects.push_back(&right);

  //----------------------------------------------------------------------------
  // Left Sphere
  //----------------------------------------------------------------------------
  Sphere left;
  left.set_transform(translation(-1.5, 0.33, -0.75) * scaling(0.33));
  RingPattern left_pattern(Color::Yellow, Color::Black);
  left_pattern.set_transform(rotation_z(-PI / 4) * rotation_x(-PI / 6) *
                             scaling(0.051));
  PatternMaterial left_material(&left_pattern);
  left_material.diffuse = 0.7;
  left_material.specular = 0.3;
  left_material.shininess = 30;
  left.set_material(&left_material);
  scene.objects.push_back(&left);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-5, 10, -5), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 4);
  camera.set_view_transform(Point(0, 1.5, -6), Point(0, 1, 0), Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-10-patterns.png");
}

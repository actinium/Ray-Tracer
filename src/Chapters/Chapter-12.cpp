#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Cube.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Plane.hpp"

void chapter12() {
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
  // Middle Cube
  //----------------------------------------------------------------------------
  Cube middle;
  middle.set_transform(rotation_y(0.5) * translation(-0.5, 0.8, 0.5) *
                       scaling(0.8));
  SimpleMaterial middle_material;
  middle_material.color = Color::Orange;
  middle_material.diffuse = 0.7;
  middle_material.specular = 0.3;
  middle.set_material(&middle_material);
  scene.objects.push_back(&middle);

  //----------------------------------------------------------------------------
  // Right Cube
  //----------------------------------------------------------------------------
  Cube right;
  right.set_transform(rotation_y(-0.2) * translation(1.5, 0.5, -0.5) *
                      scaling(0.5));
  SimpleMaterial right_material;
  right_material.color = Color::Red;
  right_material.diffuse = 0.7;
  right_material.specular = 0.3;
  right.set_material(&right_material);
  scene.objects.push_back(&right);

  //----------------------------------------------------------------------------
  // Left Cube
  //----------------------------------------------------------------------------
  Cube left;
  left.set_transform(translation(-1.5, 0.33, -0.75) * scaling(0.33));
  SimpleMaterial left_material;
  left_material.color = Color::Yellow;
  left_material.diffuse = 0.7;
  left_material.specular = 0.3;
  left.set_material(&left_material);
  scene.objects.push_back(&left);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-10, 10, -10), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 4);
  camera.set_view_transform(Point(1, 4.5, -6), Point(0, 1, 0), Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-12-cubes.png");
}

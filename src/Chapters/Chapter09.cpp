#include "Chapter09.hpp"

#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"

void chapter9() {
  Scene scene;
  //----------------------------------------------------------------------------
  // Floor
  //----------------------------------------------------------------------------
  Plane floor;
  Material wall_floor_material;
  wall_floor_material.color = Color::Lightgrey;
  wall_floor_material.specular = 0;
  floor.set_material(wall_floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Middle Sphere
  //----------------------------------------------------------------------------
  Sphere middle;
  middle.set_transform(translation(-0.5, 1, 0.5));
  Material middle_material;
  middle_material.color = Color::Red;
  middle_material.diffuse = 0.7;
  middle_material.specular = 0.3;
  middle.set_material(middle_material);
  scene.objects.push_back(&middle);

  //----------------------------------------------------------------------------
  // Right Sphere
  //----------------------------------------------------------------------------
  Sphere right;
  right.set_transform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
  Material right_material;
  right_material.color = Color::Blue;
  right_material.diffuse = 0.7;
  right_material.specular = 0.3;
  right.set_material(right_material);
  scene.objects.push_back(&right);

  //----------------------------------------------------------------------------
  // Left Sphere
  //----------------------------------------------------------------------------
  Sphere left;
  left.set_transform(translation(-1.5, 0.33, -0.75) *
                     scaling(0.33, 0.33, 0.33));
  Material left_material;
  left_material.color = Color::Green;
  left_material.diffuse = 0.7;
  left_material.specular = 0.3;
  left.set_material(left_material);
  scene.objects.push_back(&left);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-10, 10, -10), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 3);
  camera.set_view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-09-planes.png");
}

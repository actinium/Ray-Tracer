
#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Cube.hpp"
#include "Scene/Objects/Group.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "Scene/Scene.hpp"

void extra_mirror() {
  Scene scene;

  //----------------------------------------------------------------------------
  // Floor
  //----------------------------------------------------------------------------
  Plane floor;
  SimpleMaterial floor_material;
  floor_material.color = Color::White;
  floor_material.specular = 0;
  floor.set_material(&floor_material);
  scene.objects.push_back(&floor);

  //----------------------------------------------------------------------------
  // Mirror
  //----------------------------------------------------------------------------
  Group mirror;
  scene.objects.push_back(&mirror);
  mirror.set_transform(rotation_y(PI / 7) * translation(-0.2, 1, 1));

  Cube frame;
  mirror.add_child(&frame);
  SimpleMaterial frame_material;
  frame_material.color = Color::Grey;
  frame_material.specular = 0;
  frame.set_material(&frame_material);
  frame.set_transform(scaling(2, 1, 0.05));

  Cube reflective_surface;
  mirror.add_child(&reflective_surface);
  SimpleMaterial reflective_material;
  reflective_material.color = Color::Black;
  reflective_material.diffuse = 0.95;
  reflective_material.specular = 0.95;
  reflective_material.shininess = 200;
  reflective_material.reflective = 0.8;
  reflective_surface.set_material(&reflective_material);
  reflective_surface.set_transform(translation(0, 0, -0.05) *
                                   scaling(2, 1, 0.00001));

  //----------------------------------------------------------------------------
  // Spheres
  //----------------------------------------------------------------------------
  SimpleMaterial sphere_material;
  sphere_material.color = Color::Black;
  sphere_material.diffuse = 0.95;
  sphere_material.specular = 0.95;
  sphere_material.shininess = 200;
  sphere_material.reflective = 0.8;

  Sphere sphere1;
  scene.objects.push_back(&sphere1);
  sphere1.set_transform(translation(0.0, 0.2, 0.0) * scaling(0.2));
  sphere1.set_material(&sphere_material);

  Sphere sphere2;
  scene.objects.push_back(&sphere2);
  sphere2.set_transform(translation(-2.0, 0.2, -0.2) * scaling(0.2));
  sphere2.set_material(&sphere_material);

  Sphere sphere3;
  scene.objects.push_back(&sphere3);
  sphere3.set_transform(translation(-1.0, 0.2, -1.5) * scaling(0.2));
  sphere3.set_material(&sphere_material);

  Sphere sphere4;
  scene.objects.push_back(&sphere4);
  sphere4.set_transform(translation(0.7, 0.2, -1.7) * scaling(0.2));
  sphere4.set_material(&sphere_material);

  //----------------------------------------------------------------------------
  // Cubes
  //----------------------------------------------------------------------------
  Cube cube1;
  scene.objects.push_back(&cube1);
  SimpleMaterial cube1_material;
  cube1_material.color = Color::Orange;
  cube1_material.diffuse = 0.95;
  cube1_material.specular = 0.95;
  cube1.set_material(&cube1_material);
  cube1.set_transform(translation(-1, 0.2, 0.5) * scaling(0.2));

  Cube cube2;
  scene.objects.push_back(&cube2);
  SimpleMaterial cube2_material;
  cube2_material.color = Color::Green;
  cube2_material.diffuse = 0.95;
  cube2_material.specular = 0.95;
  cube2.set_material(&cube2_material);
  cube2.set_transform(translation(-0.2, 0.15, -1.5) * scaling(0.15) *
                      rotation_y(PI / 4));

  Cube cube3;
  scene.objects.push_back(&cube3);
  SimpleMaterial cube3_material;
  cube3_material.color = Color::Purple;
  cube3_material.diffuse = 0.95;
  cube3_material.specular = 0.95;
  cube3.set_material(&cube3_material);
  cube3.set_transform(translation(0.7, 0.21, -0.5) * scaling(0.21) *
                      rotation_y(PI / 7));

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(0, 10, -10), Color(0.9, 0.9, 0.9));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 4);
  camera.set_view_transform(Point(2, 4, -8), Point(0, 1, -1), Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/extra-07-mirror.png");
}

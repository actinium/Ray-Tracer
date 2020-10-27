#include "Core/Constants.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Cylinder.hpp"
#include "Scene/Objects/Group.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"

namespace {

Object* hexagon_corner() {
  Sphere* corner = new Sphere();
  corner->set_transform(translation(0, 0, -1) * scaling(0.25, 0.25, 0.25));
  return corner;
}

Object* hexagon_edge() {
  Cylinder* edge = new Cylinder();
  edge->minimum = 0;
  edge->maximum = 1;
  edge->set_transform(translation(0, 0, -1) * rotation_y(-PI / 6) *
                      rotation_z(-PI / 2) * scaling(0.25, 1, 0.25));
  return edge;
}

Object* hexagon_side() {
  Group* side = new Group();
  side->add_child(hexagon_corner());
  side->add_child(hexagon_edge());
  return side;
}

Object* hexagon() {
  Group* hex = new Group();
  for (int n = 0; n < 6; ++n) {
    Object* side = hexagon_side();
    side->set_transform(rotation_y(n * PI / 3));
    hex->add_child(side);
  }
  return hex;
}

void render_groups() {
  Scene scene;

  //----------------------------------------------------------------------------
  // Hexagons
  //----------------------------------------------------------------------------
  Object* hex1 = hexagon();
  scene.objects.push_back(hex1);

  Object* hex2 = hexagon();
  hex2->set_transform(translation(-2.5, 0, 0));
  scene.objects.push_back(hex2);

  Object* hex3 = hexagon();
  hex3->set_transform(translation(2.5, 0, 0));
  scene.objects.push_back(hex3);

  Object* hex4 = hexagon();
  hex4->set_transform(translation(-1.25, 0, 2.25));
  scene.objects.push_back(hex4);

  Object* hex5 = hexagon();
  hex5->set_transform(translation(1.25, 0, 2.25));
  scene.objects.push_back(hex5);

  Object* hex6 = hexagon();
  hex6->set_transform(translation(-1.25, 0, -2.25));
  scene.objects.push_back(hex6);

  Object* hex7 = hexagon();
  hex7->set_transform(translation(1.25, 0, -2.25));
  scene.objects.push_back(hex7);

  //----------------------------------------------------------------------------
  // Light
  //----------------------------------------------------------------------------
  Light light(Point(-5, 10, -5), Color(1, 1, 1));
  scene.lights.push_back(&light);

  //----------------------------------------------------------------------------
  // Camera
  //----------------------------------------------------------------------------
  Camera camera(1920, 1080, PI / 4);
  camera.set_view_transform(Point(1, 5.8, -6), Point(0.2, -1, 0),
                            Vector(0, 1, 0));

  Image image = camera.render(scene);
  image.save_as_png("images/chapter-14-groups.png");
}
}  // namespace

void chapter14() { render_groups(); }

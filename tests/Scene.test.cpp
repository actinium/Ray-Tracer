#include "Core/Color.hpp"
#include "Core/Lighting.hpp"
#include "Core/Point.hpp"
#include "Core/Transformations.hpp"
#include "Core/Vector.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "Scene/Scene.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("Creating a scene", "[Scene]") {
  Scene scene;
  REQUIRE(scene.objects.empty());
  REQUIRE(scene.lights.empty());
}

TEST_CASE("The default scene", "[Scene]") {
  Light light(Point(-10, 10, -10), Color(1, 1, 1));

  Sphere s1;
  SimpleMaterial m;
  m.color = Color(0.8, 1.0, 0.6);
  m.diffuse = 0.7;
  m.specular = 0.2;
  s1.set_material(&m);

  Sphere s2;
  s2.set_transform(scaling(0.5, 0.5, 0.5));
  Scene scene = default_scene;

  REQUIRE_THAT(scene.lights.front()->position, Equals(light.position));
  REQUIRE_THAT(scene.lights.front()->intensity, Equals(light.intensity));
  REQUIRE(scene.objects.size() == 2);

  // scene contains s1
  const Sphere* o1 = dynamic_cast<const Sphere*>(scene.objects[0]);
  REQUIRE(o1 != nullptr);
  REQUIRE_THAT(o1->transform(), Equals(s1.transform()));
  const SimpleMaterial& o1m =
      dynamic_cast<const SimpleMaterial&>(o1->material());
  const SimpleMaterial& s1m =
      dynamic_cast<const SimpleMaterial&>(s1.material());
  REQUIRE_THAT(o1m, Equals(s1m));

  // scene contains s2
  const Sphere* o2 = dynamic_cast<const Sphere*>(scene.objects[1]);
  REQUIRE(o2 != nullptr);
  REQUIRE_THAT(o2->transform(), Equals(s2.transform()));
  const SimpleMaterial& o2m =
      dynamic_cast<const SimpleMaterial&>(o2->material());
  const SimpleMaterial& s2m =
      dynamic_cast<const SimpleMaterial&>(s2.material());
  REQUIRE_THAT(o2m, Equals(s2m));
}

TEST_CASE("Intersect a scene with a ray", "[Scene]") {
  Scene scene = default_scene;
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = scene.intersect(r);
  REQUIRE(xs.size() == 4);
  REQUIRE(xs[0].t == Approx(4));
  REQUIRE(xs[1].t == Approx(4.5));
  REQUIRE(xs[2].t == Approx(5.5));
  REQUIRE(xs[3].t == Approx(6));
}

//------------------------------------------------------------------------------
// Shading
//------------------------------------------------------------------------------
TEST_CASE("Shading an intersection", "[Scene]") {
  Scene scene = default_scene;

  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  const Object* shape = scene.objects.front();
  Intersection i(4, shape);
  PreparedComputations comps = prepare_computations(i, r);
  Color c = shade_hit(scene, comps);
  REQUIRE_THAT(c, Equals(Color(0.380661, 0.475826, 0.285496)));
}

TEST_CASE("Shading an intersection from the inside", "[Scene]") {
  Scene scene = default_scene;
  Light light(Point(0, 0.25, 0), Color(1, 1, 1));
  scene.lights.front() = &light;

  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  const Object* shape = scene.objects[1];
  Intersection i(0.5, shape);
  PreparedComputations comps = prepare_computations(i, r);
  Color c = shade_hit(scene, comps);
  REQUIRE_THAT(c, Equals(Color(0.90498, 0.90498, 0.90498)));
}

TEST_CASE("Shading an intersection with multiple lights", "[Scene]") {
  Scene scene = default_scene;

  scene.lights.erase(scene.lights.begin());
  Light red(Point(-10, 10, -10), Color(1, 0, 0));
  Light green(Point(-10, 10, -10), Color(0, 1, 0));
  Light blue(Point(-10, 10, -10), Color(0, 0, 1));
  scene.lights.push_back(&red);
  scene.lights.push_back(&green);
  scene.lights.push_back(&blue);

  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  const Object* shape = scene.objects.front();
  Intersection i(4, shape);
  PreparedComputations comps = prepare_computations(i, r);
  Color c = shade_hit(scene, comps);
  REQUIRE_THAT(c, Equals(Color(0.380661, 0.475826, 0.285496)));
}

TEST_CASE("The color when a ray misses", "[Scene]") {
  Scene scene = default_scene;

  Ray r(Point(0, 0, -5), Vector(0, 1, 0));
  Color c = color_at(scene, r);
  REQUIRE_THAT(c, Equals(Color(0, 0, 0)));
}

TEST_CASE("The color when a ray hits", "[Scene]") {
  Scene scene = default_scene;

  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Color c = color_at(scene, r);
  REQUIRE_THAT(c, Equals(Color(0.380661, 0.475826, 0.285496)));
}

TEST_CASE("The color with an intersection behind the ray", "[Scene]") {
  Scene scene = default_scene;

  Sphere outer = default_sphere_1;
  SimpleMaterial m_outer = default_material_1;
  m_outer.ambient = 1;
  outer.set_material(&m_outer);

  Sphere inner = default_sphere_2;
  SimpleMaterial m_inner = default_material_2;
  m_inner.ambient = 1;
  inner.set_material(&m_inner);

  scene.objects[0] = &outer;
  scene.objects[1] = &inner;

  Ray r(Point(0, 0, 0.75), Vector(0, 0, -1));
  Color c = color_at(scene, r);
  REQUIRE_THAT(c, Equals(Color(m_inner.color)));
}

//------------------------------------------------------------------------------
// Shadows
//------------------------------------------------------------------------------
TEST_CASE("There is no shadow when nothing is collinear with point and light",
          "[Scene]") {
  Scene scene = default_scene;
  Point p(0, 10, 0);
  REQUIRE_FALSE(is_shadowed(p, *scene.lights.front(), scene));
}

TEST_CASE("The shadow when an object is between the point and the light",
          "[Scene]") {
  Scene scene = default_scene;
  Point p(10, -10, 10);
  REQUIRE(is_shadowed(p, *scene.lights.front(), scene));
}
TEST_CASE("There is no shadow when an object is behind the light", "[Scene]") {
  Scene scene = default_scene;
  Point p(-20, 20, -20);
  REQUIRE_FALSE(is_shadowed(p, *scene.lights.front(), scene));
}

TEST_CASE("There is no shadow when an object is behind the point", "[Scene]") {
  Scene scene = default_scene;
  Point p(-2, 2, -2);
  REQUIRE_FALSE(is_shadowed(p, *scene.lights.front(), scene));
}

TEST_CASE("shade_hit() is given an intersection in shadow", "[Scene]") {
  Scene scene;
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  scene.lights.push_back(&light);

  Sphere s1;
  scene.objects.push_back(&s1);

  Sphere s2;
  s2.set_transform(translation(0, 0, 10));
  scene.objects.push_back(&s2);

  Ray ray(Point(0, 0, 5), Vector(0, 0, 1));
  Intersection i(4, &s2);
  PreparedComputations comps = prepare_computations(i, ray);
  Color c = shade_hit(scene, comps);
  REQUIRE_THAT(c, Equals(Color(0.1, 0.1, 0.1)));
}

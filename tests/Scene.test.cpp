#include "Core/Color.hpp"
#include "Core/Point.hpp"
#include "Core/Transformations.hpp"
#include "Core/Vector.hpp"
#include "Scene/Lights/Light.hpp"
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
  Material m;
  m.color = Color(0.8, 1.0, 0.6);
  m.diffuse = 0.7;
  m.specular = 0.2;
  s1.set_material(m);

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
  REQUIRE_THAT(o1->material(), Equals(s1.material()));

  // scene contains s2
  const Sphere* o2 = dynamic_cast<const Sphere*>(scene.objects[1]);
  REQUIRE(o2 != nullptr);
  REQUIRE_THAT(o2->transform(), Equals(s2.transform()));
  REQUIRE_THAT(o2->material(), Equals(s2.material()));
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

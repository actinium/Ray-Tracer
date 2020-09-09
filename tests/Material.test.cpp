#include <cmath>

#include "Core/Lighting.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/Material.hpp"
#include "Scene/Objects/Materials/PatternMaterial.hpp"
#include "Scene/Objects/Materials/Patterns/StripePattern.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

TEST_CASE("The default material", "[Material]") {
  SimpleMaterial m;
  REQUIRE_THAT(m.color, Equals(Color(1, 1, 1)));
  REQUIRE(m.ambient == Approx(0.1));
  REQUIRE(m.diffuse == Approx(0.9));
  REQUIRE(m.specular == Approx(0.9));
  REQUIRE(m.shininess == Approx(200.0));
}

//------------------------------------------------------------------------------
// Lighting
//------------------------------------------------------------------------------
TEST_CASE("Lighting with the eye between the light and the surface",
          "[Material]") {
  SimpleMaterial m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv, false);
  REQUIRE_THAT(result, Equals(Color(1.9, 1.9, 1.9)));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°",
          "[Material]") {
  SimpleMaterial m;
  Point position = Point::Origin;
  Vector eyev(0, sqrt(2) / 2, -sqrt(2) / 2);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv, false);
  REQUIRE_THAT(result, Equals(Color(1.0, 1.0, 1.0)));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°",
          "[Material]") {
  SimpleMaterial m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv, false);
  REQUIRE_THAT(result, Equals(Color(0.7364, 0.7364, 0.7364)));
}

TEST_CASE("Lighting with eye in the path of the reflection vector",
          "[Material]") {
  SimpleMaterial m;
  Point position = Point::Origin;
  Vector eyev(0, -sqrt(2) / 2, -sqrt(2) / 2);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv, false);
  REQUIRE_THAT(result, Equals(Color(1.6364, 1.6364, 1.6364)));
}

TEST_CASE("Lighting with the light behind the surface", "[Material]") {
  SimpleMaterial m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, 10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv, false);
  REQUIRE_THAT(result, Equals(Color(0.1, 0.1, 0.1)));
}

//------------------------------------------------------------------------------
// Lighting with Shadows
//------------------------------------------------------------------------------
TEST_CASE("Lighting with the surface in shadow", "[Material]") {
  SimpleMaterial m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  bool in_shadow = true;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  REQUIRE_THAT(result, Equals(Color(0.1, 0.1, 0.1)));
}

//------------------------------------------------------------------------------
// Lighting with a Pattern
//------------------------------------------------------------------------------
TEST_CASE("Lighting with a pattern applied", "[Material]") {
  PatternMaterial m;
  Point position = Point::Origin;
  StripePattern sp(Color(1, 1, 1), Color(0, 0, 0));
  m.pattern = &sp;
  m.ambient = 1;
  m.diffuse = 0;
  m.specular = 0;

  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));

  Color c1 = lighting(m, light, Point(0.9, 0, 0), eyev, normalv, false);
  Color c2 = lighting(m, light, Point(1.1, 0, 0), eyev, normalv, false);
  REQUIRE_THAT(c1, Equals(Color(1, 1, 1)));
  REQUIRE_THAT(c2, Equals(Color(0, 0, 0)));
}

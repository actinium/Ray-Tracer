#include <cmath>

#include "Core/Lighting.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/Material.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

TEST_CASE("The default material", "[Material]") {
  Material m;
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
  Material m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv);
  REQUIRE_THAT(result, Equals(Color(1.9, 1.9, 1.9)));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°",
          "[Material]") {
  Material m;
  Point position = Point::Origin;
  Vector eyev(0, sqrt(2) / 2, -sqrt(2) / 2);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv);
  REQUIRE_THAT(result, Equals(Color(1.0, 1.0, 1.0)));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°",
          "[Material]") {
  Material m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv);
  REQUIRE_THAT(result, Equals(Color(0.7364, 0.7364, 0.7364)));
}

TEST_CASE("Lighting with eye in the path of the reflection vector",
          "[Material]") {
  Material m;
  Point position = Point::Origin;
  Vector eyev(0, -sqrt(2) / 2, -sqrt(2) / 2);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv);
  REQUIRE_THAT(result, Equals(Color(1.6364, 1.6364, 1.6364)));
}

TEST_CASE("Lighting with the light behind the surface", "[Material]") {
  Material m;
  Point position = Point::Origin;
  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light light(Point(0, 0, 10), Color(1, 1, 1));
  Color result = lighting(m, light, position, eyev, normalv);
  REQUIRE_THAT(result, Equals(Color(0.1, 0.1, 0.1)));
}

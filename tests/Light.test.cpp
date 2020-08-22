#include "Core/Color.hpp"
#include "Core/Point.hpp"
#include "Scene/Lights/Light.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("A point light has a position and intensity", "[Light]") {
  Point position(0, 0, 0);
  Color intensity(1, 1, 1);
  Light light(position, intensity);
  REQUIRE_THAT(light.position, Equals(position));
  REQUIRE_THAT(light.intensity, Equals(intensity));
}

#include "Core/Math.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default vector is (0, 0, 0, 0)", "[Vector]") {
  Vector v;
  REQUIRE_THAT(v, Equals(Vector(0, 0, 0)));
}

TEST_CASE("Add two vectors", "[Vector]") {
  Vector v1(1.1, 2.3, 3.0);
  Vector v2(8.5, -1, 0);
  Vector v = v1 + v2;
  REQUIRE_THAT(v, Equals(Vector(9.6, 1.3, 3.0)));
}

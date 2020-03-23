#include "catch.hpp"

#include "Core/Math.hpp"
#include "Core/Vector.hpp"

TEST_CASE("The default vector is (0, 0, 0, 0)", "[Vector]") {
  Vector v;
  REQUIRE(v.x == 0);
  REQUIRE(v.y == 0);
  REQUIRE(v.z == 0);
  REQUIRE(v.w == 0);
}

TEST_CASE("Add two vectors", "[Vector]") {
  Vector v1(1.1, 2.3, 3.0);
  Vector v2(8.5, -1, 0);
  Vector v = v1 + v2;
  REQUIRE(v.x == Approx(9.6));
  REQUIRE(v.y == Approx(1.3));
  REQUIRE(v.z == Approx(3.0));
  REQUIRE(v.w == Approx(0));
}

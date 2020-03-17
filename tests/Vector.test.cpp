#include "catch.hpp"

#include "Core/Vector.hpp"

TEST_CASE("The default vector is (0, 0, 0, 0)", "[Vector]") {
  Vector v;
  REQUIRE(v.x == 0);
  REQUIRE(v.y == 0);
  REQUIRE(v.z == 0);
  REQUIRE(v.w == 0);
}

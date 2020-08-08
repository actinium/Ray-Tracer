#include "Core/Math.hpp"
#include "Core/Point.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default point is (0, 0, 0, 1)", "[Point]") {
  Point p;
  REQUIRE(p.x == Approx(0));
  REQUIRE(p.y == Approx(0));
  REQUIRE(p.z == Approx(0));
  REQUIRE(p.w == Approx(1));
}

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
TEST_CASE("Adding a vector to a point", "[Point]") {
  REQUIRE_THAT(Point(-1.1, 0, 3.0) + Vector(4.1, -0.1, 0),
               Equals(Point(3, -0.1, 3.0)));
}

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
TEST_CASE("Subtracting a vector from a point", "[Point]") {
  REQUIRE_THAT(Point(-10.01, 0, 3.14) - Vector(2.5, -0.01, 1.0),
               Equals(Point(-12.51, 0.01, 2.14)));
}

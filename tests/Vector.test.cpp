#include "Core/Math.hpp"
#include "Core/Point.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default vector is (0, 0, 0, 0)", "[Vector]") {
  Vector v;
  REQUIRE_THAT(v, Equals(Vector(0, 0, 0)));
}

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
TEST_CASE("Add two vectors", "[Vector]") {
  Vector v1(1.1, 2.3, 3.0);
  Vector v2(8.5, -1, 0);
  Vector v = v1 + v2;
  REQUIRE_THAT(v, Equals(Vector(9.6, 1.3, 3.0)));
}

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
TEST_CASE("Subtracting a vector from a vector", "[Vector]") {
  Vector v1(1.1, 2.3, 3.0);
  Vector v2(8.5, -1, 0);
  Vector v = v1 - v2;
  REQUIRE_THAT(v, Equals(Vector(-7.4, 3.3, 3.0)));
}

TEST_CASE("Subtracting a point from a point", "[Vector]") {
  Point p1(1.1, -2.3, 4.0);
  Point p2(4.1, 1, 0);
  Vector v = p1 - p2;
  REQUIRE_THAT(v, Equals(Vector(-3, -3.3, 4.0)));
}

//------------------------------------------------------------------------------
// Negation
//------------------------------------------------------------------------------
TEST_CASE("Negating a vector", "[Vector]") {
  Vector v(1.1, -2.3, 3.1234);
  REQUIRE_THAT(-v, Equals(Vector(-1.1, 2.3, -3.1234)));
}

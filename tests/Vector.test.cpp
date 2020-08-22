#include "Core/Math.hpp"
#include "Core/Point.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default vector is (0, 0, 0, 0)", "[Vector]") {
  Vector v;
  REQUIRE(v.x == Approx(0));
  REQUIRE(v.y == Approx(0));
  REQUIRE(v.z == Approx(0));
  REQUIRE(v.w == Approx(0));
}

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
TEST_CASE("Adding two vectors", "[Vector]") {
  REQUIRE_THAT(Vector(1.1, 2.3, 3.0) + Vector(8.5, -1, 0),
               Equals(Vector(9.6, 1.3, 3.0)));
}

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
TEST_CASE("Subtracting a vector from a vector", "[Vector]") {
  REQUIRE_THAT(Vector(1.1, 2.3, 3.0) - Vector(8.5, -1, 0),
               Equals(Vector(-7.4, 3.3, 3.0)));
}

TEST_CASE("Subtracting a point from a point", "[Vector]") {
  REQUIRE_THAT(Point(1.1, -2.3, 4.0) - Point(4.1, 1, 0),
               Equals(Vector(-3, -3.3, 4.0)));
}

//------------------------------------------------------------------------------
// Negation
//------------------------------------------------------------------------------
TEST_CASE("Negating a vector", "[Vector]") {
  REQUIRE_THAT(-Vector(1.1, -2.3, 3.1234), Equals(Vector(-1.1, 2.3, -3.1234)));
}

//------------------------------------------------------------------------------
// Scalar Multiplication
//------------------------------------------------------------------------------
TEST_CASE("Multiplying a vector by a scalar", "[Vector]") {
  double s = 3.2;
  Vector v(8.5, -1, 0);
  REQUIRE_THAT(s * v, Equals(Vector(27.2, -3.2, 0)));
  REQUIRE_THAT(v * s, Equals(s * v));
}

TEST_CASE("Multiplying a vector by a fraction", "[Vector]") {
  double s = 0.2;
  Vector v(8.5, 0, -1);
  REQUIRE_THAT(s * v, Equals(Vector(1.7, 0, -0.2)));
  REQUIRE_THAT(v * s, Equals(s * v));
}

//------------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------------
TEST_CASE("Calculating the dot product of two vectors", "[Vector]") {
  REQUIRE(dot(Vector(1, 2, 3), Vector(2, 3, 4)) == 20);
}

TEST_CASE("Calculating the cross product of two vectors", "[Vector]") {
  REQUIRE_THAT(cross(Vector(1, 2, 3), Vector(2, 3, 4)),
               Equals(Vector(-1, 2, -1)));
  REQUIRE_THAT(cross(Vector(2, 3, 4), Vector(1, 2, 3)),
               Equals(Vector(1, -2, 1)));
}

//------------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------------
TEST_CASE("Dividing a vector by a scalar", "[Vector]") {
  REQUIRE_THAT(Vector(8.5, -1, 0) / 3.2, Equals(Vector(2.65625, -0.3125, 0)));
}

//------------------------------------------------------------------------------
// Magnitude
//------------------------------------------------------------------------------
TEST_CASE("The magnitude of a vector", "[Vector]") {
  REQUIRE(magnitude(Vector(1, 0, 0)) == Approx(1));
  REQUIRE(magnitude(Vector(0, 1, 0)) == Approx(1));
  REQUIRE(magnitude(Vector(0, 0, 1)) == Approx(1));
  REQUIRE(magnitude(Vector(1, 2, 3)) == Approx(std::sqrt(14)));
  REQUIRE(magnitude(Vector(-1, 2, 3)) == Approx(std::sqrt(14)));
  REQUIRE(magnitude(Vector(1, -2, 3)) == Approx(std::sqrt(14)));
  REQUIRE(magnitude(Vector(1, 2, -3)) == Approx(std::sqrt(14)));
  REQUIRE(magnitude(Vector(-1, -2, -3)) == Approx(std::sqrt(14)));
}

TEST_CASE("Normalizing a vector", "[Vector]") {
  REQUIRE_THAT(normalize(Vector(4, 0, 0)), Equals(Vector(1, 0, 0)));
  REQUIRE_THAT(
      normalize(Vector(1, 2, 3)),
      Equals(Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14))));
}

TEST_CASE("The magnitude of a normalized vector", "[Vector]") {
  REQUIRE(magnitude(normalize(Vector(1, 2, 3))) == Approx(1));
}

//------------------------------------------------------------------------------
// Reflection
//------------------------------------------------------------------------------
TEST_CASE("Reflecting a vector approaching at 45°", "[Vector]") {
  Vector vector(1, -1, 0);
  Vector normal(0, 1, 0);
  REQUIRE_THAT(reflect(vector, normal), Equals(Vector(1, 1, 0)));
}

TEST_CASE("Reflecting a vector off a slanted surface", "[Vector]") {
  Vector vector(0, -1, 0);
  Vector normal(sqrt(2) / 2, sqrt(2) / 2, 0);
  REQUIRE_THAT(reflect(vector, normal), Equals(Vector(1, 0, 0)));
}

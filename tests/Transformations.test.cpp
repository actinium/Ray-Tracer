#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/Transformations.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

//------------------------------------------------------------------------------
// Translation
//------------------------------------------------------------------------------
TEST_CASE("Multiplying by a translation matrix", "[Transformation]") {
  Matrix transform = translation(5, -3, 2);
  Point p(-3, 4, 5);
  REQUIRE_THAT(transform * p, Equals(Point(2, 1, 7)));
}

TEST_CASE("Multiplying by the inverse of a translation matrix",
          "[Transformation]") {
  Matrix transform = translation(5, -3, 2);
  Matrix inv = inverse(transform);
  Point p(-3, 4, 5);
  REQUIRE_THAT(inv * p, Equals(Point(-8, 7, 3)));
}

TEST_CASE("Translation does not affect vectors", "[Transformation]") {
  Matrix transform = translation(5, -3, 2);
  Vector v(-3, 4, 5);
  REQUIRE_THAT(transform * v, Equals(v));
}

TEST_CASE(
    "The inverse of a translation matrix is movement in opposite direction",
    "[Transformation]") {
  Matrix transform = translation(0, -5, 3);
  Matrix inv = inverse(transform);
  REQUIRE_THAT(inv, Equals(translation(0, 5, -3)));
}

//------------------------------------------------------------------------------
// Scaling
//------------------------------------------------------------------------------
TEST_CASE("A scaling matrix applied to a point", "[Transformation]") {
  Matrix transform = scaling(2, 3, 4);
  Point p(-4, 6, 8);
  REQUIRE_THAT(transform * p, Equals(Point(-8, 18, 32)));
}

TEST_CASE("A scaling matrix applied to a vector", "[Transformation]") {
  Matrix transform = scaling(2, 3, 4);
  Vector v(-4, 6, 8);
  REQUIRE_THAT(transform * v, Equals(Vector(-8, 18, 32)));
}

TEST_CASE("Multiplying by the inverse of a scaling matrix",
          "[Transformation]") {
  Matrix transform = scaling(2, 3, 4);
  Matrix inv = inverse(transform);
  Vector v(-4, 6, 8);
  REQUIRE_THAT(inv * v, Equals(Vector(-2, 2, 2)));
}

TEST_CASE("Reflection is scaling by a negative value", "[Transformation]") {
  Matrix transform = scaling(-1, 1, 1);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(-2, 3, 4)));
}

//------------------------------------------------------------------------------
// Rotation
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Shearing
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Transformation chaining
//------------------------------------------------------------------------------

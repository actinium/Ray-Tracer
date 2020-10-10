#include <cmath>

#include "Core/Constants.hpp"
#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/Transformations.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

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
TEST_CASE("Rotating a point around the x axis", "[Transformation]") {
  Point p(0, 1, 0);
  Matrix half_quarter = rotation_x(PI / 4);
  Matrix full_quarter = rotation_x(PI / 2);
  REQUIRE_THAT(half_quarter * p, Equals(Point(0, sqrt(2) / 2, sqrt(2) / 2)));
  REQUIRE_THAT(full_quarter * p, Equals(Point(0, 0, 1)));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction",
          "[Transformation]") {
  Point p(0, 1, 0);
  Matrix half_quarter = rotation_x(PI / 4);
  Matrix opposite_half_quarter = rotation_x(-PI / 4);
  Matrix inv = inverse(half_quarter);
  REQUIRE_THAT(inv, Equals(opposite_half_quarter));
  REQUIRE_THAT(inv * p, Equals(Point(0, sqrt(2) / 2, -sqrt(2) / 2)));
}

TEST_CASE("Rotating a point around the y axis", "[Transformation]") {
  Point p(0, 0, 1);
  Matrix half_quarter = rotation_y(PI / 4);
  Matrix full_quarter = rotation_y(PI / 2);
  REQUIRE_THAT(half_quarter * p, Equals(Point(sqrt(2) / 2, 0, sqrt(2) / 2)));
  REQUIRE_THAT(full_quarter * p, Equals(Point(1, 0, 0)));
}

TEST_CASE("Rotating a point around the z axis", "[Transformation]") {
  Point p(0, 1, 0);
  Matrix half_quarter = rotation_z(PI / 4);
  Matrix full_quarter = rotation_z(PI / 2);
  REQUIRE_THAT(half_quarter * p, Equals(Point(-sqrt(2) / 2, sqrt(2) / 2, 0)));
  REQUIRE_THAT(full_quarter * p, Equals(Point(-1, 0, 0)));
}

//------------------------------------------------------------------------------
// Shearing
//------------------------------------------------------------------------------
TEST_CASE("A shearing transformation moves x in proportion to y",
          "[Transformation]") {
  Matrix transform = shearing(1, 0, 0, 0, 0, 0);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(5, 3, 4)));
}

TEST_CASE("A shearing transformation moves x in proportion to z",
          "[Transformation]") {
  Matrix transform = shearing(0, 1, 0, 0, 0, 0);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(6, 3, 4)));
}

TEST_CASE("A shearing transformation moves y in proportion to x",
          "[Transformation]") {
  Matrix transform = shearing(0, 0, 1, 0, 0, 0);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(2, 5, 4)));
}

TEST_CASE("A shearing transformation moves y in proportion to z",
          "[Transformation]") {
  Matrix transform = shearing(0, 0, 0, 1, 0, 0);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(2, 7, 4)));
}

TEST_CASE("A shearing transformation moves z in proportion to x",
          "[Transformation]") {
  Matrix transform = shearing(0, 0, 0, 0, 1, 0);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(2, 3, 6)));
}

TEST_CASE("A shearing transformation moves z in proportion to y",
          "[Transformation]") {
  Matrix transform = shearing(0, 0, 0, 0, 0, 1);
  Point p(2, 3, 4);
  REQUIRE_THAT(transform * p, Equals(Point(2, 3, 7)));
}

//------------------------------------------------------------------------------
// Transformation chaining
//------------------------------------------------------------------------------
TEST_CASE("Individual transformations are applied in sequence",
          "[Transformation]") {
  Point p(1, 0, 1);
  Matrix A = rotation_x(PI / 2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);
  Point p2 = A * p;
  REQUIRE_THAT(p2, Equals(Point(1, -1, 0)));
  Point p3 = B * p2;
  REQUIRE_THAT(p3, Equals(Point(5, -5, 0)));
  Point p4 = C * p3;
  REQUIRE_THAT(p4, Equals(Point(15, 0, 7)));
}

TEST_CASE("Chained transformations must be applied in reverse order",
          "[Transformation]") {
  Point p(1, 0, 1);
  Matrix A = rotation_x(PI / 2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);
  Matrix T = C * B * A;
  REQUIRE_THAT(T * p, Equals(Point(15, 0, 7)));
}

//------------------------------------------------------------------------------
// View Transform
//------------------------------------------------------------------------------
TEST_CASE("The transformation matrix for the default orientation",
          "[Transformation]") {
  Point from(0, 0, 0);
  Point to(0, 0, -1);
  Vector up(0, 1, 0);
  Matrix t = view_transform(from, to, up);
  REQUIRE_THAT(t, Equals(Matrix::Identity));
}

TEST_CASE("A view transformation matrix looking in positive z direction",
          "[Transformation]") {
  Point from(0, 0, 0);
  Point to(0, 0, 1);
  Vector up(0, 1, 0);
  Matrix t = view_transform(from, to, up);
  REQUIRE_THAT(t, Equals(scaling(-1, 1, -1)));
}

TEST_CASE("The view transformation moves the world", "[Transformation]") {
  Point from(0, 0, 8);
  Point to(0, 0, 0);
  Vector up(0, 1, 0);
  Matrix t = view_transform(from, to, up);
  REQUIRE_THAT(t, Equals(translation(0, 0, -8)));
}

TEST_CASE("An arbitrary view transformation", "[Transformation]") {
  Point from(1, 3, 2);
  Point to(4, -2, 8);
  Vector up(1, 1, 0);
  Matrix t = view_transform(from, to, up);
  REQUIRE_THAT(t,
               Equals(Matrix(-0.507093, 0.507093, 0.676123, -2.36643, 0.767716,
                             0.606092, 0.121218, -2.82843, -0.358569, 0.597614,
                             -0.717137, 0, 0, 0, 0, 1)));
}

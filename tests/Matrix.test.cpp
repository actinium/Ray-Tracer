#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default matrix is the identity matrix", "[Matrix]") {
  Matrix m;
  REQUIRE_THAT(m,
               Equals(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
  REQUIRE_THAT(m, Equals(Matrix::Identity));
}

TEST_CASE("Matrix construction", "[Matrix]") {
  double mat4[4][4] = {{1, 2, 3, 4},
                       {-1, -2, -3, -4},
                       {0.1, 0.02, 0.003, 0.0004},
                       {555, 0, 1.0, 4.3333}};
  Matrix m(mat4);
  REQUIRE_THAT(m, Equals(Matrix(1, 2, 3, 4, -1, -2, -3, -4, 0.1, 0.02, 0.003,
                                0.0004, 555, 0, 1, 4.3333)));
}

//------------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------------
TEST_CASE("Multiplying two matrices", "[Matrix]") {
  Matrix A(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
  Matrix B(-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8);
  Matrix R(20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42);
  REQUIRE_THAT(A * B, Equals(R));
}

TEST_CASE("A matrix multiplied by a vector", "[Matrix][Vector]") {
  Matrix A(1, 2, 3, 4, 0.1, 0.01, 0.2, 0.5, 10, 20, 40, 30, 11, 11, 22, 22);
  Vector b(2, 8, 5);
  Vector r = A * b;
  REQUIRE(r.x == Approx(33));
  REQUIRE(r.y == Approx(1.28));
  REQUIRE(r.z == Approx(380));
  REQUIRE(r.w == Approx(220));
}

TEST_CASE("A matrix multiplied by a point", "[Matrix][Point]") {
  Matrix A(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1);
  Point b(1, 2, 3);
  REQUIRE_THAT(A * b, Equals(Point(18, 24, 33)));
}

TEST_CASE("Multiplying a matrix by the identity matrix", "[Matrix]") {
  Matrix A(0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32);
  REQUIRE_THAT(Matrix::Identity * A, Equals(A));
  REQUIRE_THAT(Matrix::Identity * Matrix::Identity, Equals(Matrix::Identity));
}

TEST_CASE("Multiplying the identity matrix by a vector", "[Matrix][Vector]") {
  REQUIRE_THAT(Matrix::Identity * Vector(1, 2, 3), Equals(Vector(1, 2, 3)));
  REQUIRE_THAT(Matrix::Identity * Vector(0, 0, 0), Equals(Vector(0, 0, 0)));
  REQUIRE_THAT(Matrix::Identity * Vector(-1, 2, -3), Equals(Vector(-1, 2, -3)));
}

TEST_CASE("Multiplying the identity matrix by a point", "[Matrix][Point]") {
  REQUIRE_THAT(Matrix::Identity * Point(1, 2, 3), Equals(Point(1, 2, 3)));
  REQUIRE_THAT(Matrix::Identity * Point(0, 0, 0), Equals(Point(0, 0, 0)));
  REQUIRE_THAT(Matrix::Identity * Point(-1, 2, -3), Equals(Point(-1, 2, -3)));
}

//------------------------------------------------------------------------------
// Transposition
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Inversion
//------------------------------------------------------------------------------

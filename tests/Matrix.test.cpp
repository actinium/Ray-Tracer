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
TEST_CASE("Transposing a matrix", "[Matrix]") {
  REQUIRE_THAT(
      transpose(Matrix(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8)),
      Equals(Matrix(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8)));
}

TEST_CASE("Transposing the identity matrix", "[Matrix]") {
  REQUIRE_THAT(transpose(Matrix::Identity), Equals(Matrix::Identity));
}

//------------------------------------------------------------------------------
// Inversion
//------------------------------------------------------------------------------
TEST_CASE("Calculating the inverse of a matrix", "[Matrix]") {
  REQUIRE_THAT(
      inverse(Matrix(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4)),
      Equals(Matrix(0.218045, 0.451128, 0.240602, -0.0451128, -0.808271,
                    -1.45677, -0.443609, 0.520677, -0.0789474, -0.223684,
                    -0.0526316, 0.197368, -0.522556, -0.81391, -0.300752,
                    0.306391)));
  REQUIRE_THAT(
      inverse(Matrix(8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4)),
      Equals(Matrix(-0.153846, -0.153846, -0.282051, -0.538462, -0.0769231,
                    0.123077, 0.025641, 0.0307692, 0.358974, 0.358974, 0.435897,
                    0.923077, -0.692308, -0.692308, -0.769231, -1.92308)));
  REQUIRE_THAT(
      inverse(Matrix(9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2)),
      Equals(Matrix(-0.0407407, -0.0777778, 0.144444, -0.222222, -0.0777778,
                    0.0333333, 0.366667, -0.333333, -0.0290123, -0.146296,
                    -0.109259, 0.12963, 0.177778, 0.0666667, -0.266667,
                    0.333333)));
}

TEST_CASE("Multiplying a product by its inverse", "[Matrix]") {
  Matrix A(3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1);
  Matrix B(8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5);
  Matrix C = A * B;
  REQUIRE_THAT(C * inverse(B), Equals(A));
}

TEST_CASE("Multiplying a matrix by its inverse", "[Matrix]") {
  Matrix A(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);
  REQUIRE_THAT(A * inverse(A), Equals(Matrix::Identity));
  Matrix B(8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4);
  REQUIRE_THAT(B * inverse(B), Equals(Matrix::Identity));
  Matrix C(9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2);
  REQUIRE_THAT(C * inverse(C), Equals(Matrix::Identity));
}

TEST_CASE("Calculating the inverse of the inverse of a matrix", "[Matrix]") {
  Matrix A(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);
  REQUIRE_THAT(inverse(inverse(A)), Equals(A));
  Matrix B(8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4);
  REQUIRE_THAT(inverse(inverse(B)), Equals(B));
  Matrix C(9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2);
  REQUIRE_THAT(inverse(inverse(C)), Equals(C));
}

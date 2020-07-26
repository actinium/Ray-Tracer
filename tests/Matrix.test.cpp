#include "catch.hpp"

#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/Vector.hpp"

TEST_CASE("The default matrix is the identity matrix", "[Matrix]") {
  Matrix m;
  REQUIRE(m.mat4[0][0] == Approx(1));
  REQUIRE(m.mat4[0][1] == Approx(0));
  REQUIRE(m.mat4[0][2] == Approx(0));
  REQUIRE(m.mat4[0][3] == Approx(0));
  REQUIRE(m.mat4[1][0] == Approx(0));
  REQUIRE(m.mat4[1][1] == Approx(1));
  REQUIRE(m.mat4[1][2] == Approx(0));
  REQUIRE(m.mat4[1][3] == Approx(0));
  REQUIRE(m.mat4[2][0] == Approx(0));
  REQUIRE(m.mat4[2][1] == Approx(0));
  REQUIRE(m.mat4[2][2] == Approx(1));
  REQUIRE(m.mat4[2][3] == Approx(0));
  REQUIRE(m.mat4[3][0] == Approx(0));
  REQUIRE(m.mat4[3][1] == Approx(0));
  REQUIRE(m.mat4[3][2] == Approx(0));
  REQUIRE(m.mat4[3][3] == Approx(1));
}

TEST_CASE("Matrix construction", "[Matrix]") {
  double mat4[4][4] = {{1, 2, 3, 4},
                       {-1, -2, -3, -4},
                       {0.1, 0.02, 0.003, 0.0004},
                       {555, 0, 1.0, 4.3333}};
  Matrix m(mat4);
  REQUIRE(m.mat4[0][0] == Approx(1));
  REQUIRE(m.mat4[0][1] == Approx(2));
  REQUIRE(m.mat4[0][2] == Approx(3));
  REQUIRE(m.mat4[0][3] == Approx(4));
  REQUIRE(m.mat4[1][0] == Approx(-1));
  REQUIRE(m.mat4[1][1] == Approx(-2));
  REQUIRE(m.mat4[1][2] == Approx(-3));
  REQUIRE(m.mat4[1][3] == Approx(-4));
  REQUIRE(m.mat4[2][0] == Approx(0.1));
  REQUIRE(m.mat4[2][1] == Approx(0.02));
  REQUIRE(m.mat4[2][2] == Approx(0.003));
  REQUIRE(m.mat4[2][3] == Approx(0.0004));
  REQUIRE(m.mat4[3][0] == Approx(555));
  REQUIRE(m.mat4[3][1] == Approx(0));
  REQUIRE(m.mat4[3][2] == Approx(1));
  REQUIRE(m.mat4[3][3] == Approx(4.3333));
}

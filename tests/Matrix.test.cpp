#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default matrix is the identity matrix", "[Matrix]") {
  Matrix m;
  REQUIRE_THAT(m,
               Equals(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
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

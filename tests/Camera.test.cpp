#include <cmath>
#include <cstddef>

#include "Core/Constants.hpp"
#include "Core/Image.hpp"
#include "Core/Matrix.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Camera.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

TEST_CASE("Constructing a camera", "[Camera]") {
  std::size_t width = 160;
  std::size_t height = 120;
  double field_of_view = PI / 2;
  Camera camera(width, height, field_of_view);
  REQUIRE(camera.width == 160);
  REQUIRE(camera.height == 120);
  REQUIRE(camera.field_of_view == PI / 2);
  REQUIRE_THAT(camera.transform(), Equals(Matrix::Identity));
}

//------------------------------------------------------------------------------
// Pixel Size
//------------------------------------------------------------------------------
TEST_CASE("The pixel size for a horizontal canvas", "[Camera]") {
  Camera camera(200, 125, PI / 2);
  REQUIRE(camera.pixel_size == Approx(0.01));
}

TEST_CASE("The pixel size for a vertical canvas", "[Camera]") {
  Camera camera(125, 200, PI / 2);
  REQUIRE(camera.pixel_size == Approx(0.01));
}

//------------------------------------------------------------------------------
// Ray from Camera
//------------------------------------------------------------------------------
TEST_CASE("Constructing a ray through the center of the canvas", "[Camera]") {
  Camera camera(201, 101, PI / 2);
  Ray r = camera.ray_for_pixel(100, 50);
  REQUIRE_THAT(r.origin, Equals(Point(0, 0, 0)));
  REQUIRE_THAT(r.direction, Equals(Vector(0, 0, -1)));
}

TEST_CASE("Constructing a ray through a corner of the canvas", "[Camera]") {
  Camera camera(201, 101, PI / 2);
  Ray r = camera.ray_for_pixel(0, 0);
  REQUIRE_THAT(r.origin, Equals(Point(0, 0, 0)));
  REQUIRE_THAT(r.direction, Equals(Vector(0.66519, 0.33259, -0.66851)));
}

TEST_CASE("Constructing a ray when the camera is transformed", "[Camera]") {
  Camera camera(201, 101, PI / 2);
  camera.set_transform(rotation_y(PI / 4) * translation(0, -2, 5));
  Ray r = camera.ray_for_pixel(100, 50);
  REQUIRE_THAT(r.origin, Equals(Point(0, 2, -5)));
  REQUIRE_THAT(r.direction, Equals(Vector(sqrt(2) / 2, 0, -sqrt(2) / 2)));
}

//------------------------------------------------------------------------------
// Rendering
//------------------------------------------------------------------------------
TEST_CASE("Rendering a world with a camera", "[Camera]") {
  Scene scene = default_scene;

  Camera camera(11, 11, PI / 2);
  Point from(0, 0, -5);
  Point to(0, 0, 0);
  Vector up(0, 1, 0);
  camera.set_transform(view_transform(from, to, up));

  Image image = camera.render(scene);
  REQUIRE_THAT(image(5, 5), Equals(Color(0.380661, 0.475826, 0.285496)));
}

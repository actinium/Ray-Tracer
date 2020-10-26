#include <cmath>

#include "Core/Intersection.hpp"
#include "Core/Math.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

TEST_CASE("A ray intersects a sphere at two points", "[Sphere]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(4.0));
  REQUIRE(xs[1].t == Approx(6.0));
}

TEST_CASE("A ray intersects a sphere at a tangent", "[Sphere]") {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(5.0));
  REQUIRE(xs[1].t == Approx(5.0));
}

TEST_CASE("A ray misses a sphere", "[Sphere]") {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere", "[Sphere]") {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(-1.0));
  REQUIRE(xs[1].t == Approx(1.0));
}

TEST_CASE("A sphere is behind a ray", "[Sphere]") {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(-6.0));
  REQUIRE(xs[1].t == Approx(-4.0));
}

//------------------------------------------------------------------------------
// Transformation
//------------------------------------------------------------------------------
TEST_CASE("A sphere's default transformation", "[Sphere]") {
  Sphere s;
  REQUIRE_THAT(s.transform(), Equals(Matrix::Identity));
}

TEST_CASE("Changing a sphere's transformation", "[Sphere]") {
  Sphere s;
  Matrix t = translation(2, 3, 4);
  s.set_transform(t);
  REQUIRE_THAT(s.transform(), Equals(t));
}

TEST_CASE("Intersecting a scaled sphere with a ray", "[Sphere]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.set_transform(scaling(2, 2, 2));
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(3));
  REQUIRE(xs[1].t == Approx(7));
}

TEST_CASE("Intersecting a translated sphere with a ray", "[Sphere]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.set_transform(translation(5, 0, 0));
  Intersections xs;
  s.intersect(r, xs);
  REQUIRE(xs.size() == 0);
}

//------------------------------------------------------------------------------
// Normal Vector
//------------------------------------------------------------------------------
TEST_CASE("The normal on a sphere at a point on the x axis", "[Sphere]") {
  Sphere s;
  Vector n = s.normal_at(Point(1, 0, 0));
  REQUIRE_THAT(n, Equals(Vector(1, 0, 0)));
}

TEST_CASE("The normal on a sphere at a point on the y axis", "[Sphere]") {
  Sphere s;
  Vector n = s.normal_at(Point(0, 1, 0));
  REQUIRE_THAT(n, Equals(Vector(0, 1, 0)));
}

TEST_CASE("The normal on a sphere at a point on the z axis", "[Sphere]") {
  Sphere s;
  Vector n = s.normal_at(Point(0, 0, 1));
  REQUIRE_THAT(n, Equals(Vector(0, 0, 1)));
}

TEST_CASE("The normal on a sphere at a nonaxial point", "[Sphere]") {
  Sphere s;
  Vector n = s.normal_at(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  REQUIRE_THAT(n, Equals(Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3)));
}

TEST_CASE("The normal is a normalized vector", "[Sphere]") {
  Sphere s;
  Vector n = s.normal_at(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  REQUIRE_THAT(n, Equals(normalize(n)));
}

TEST_CASE("Computing the normal on a translated sphere", "[Sphere]") {
  Sphere s;
  s.set_transform(translation(0, 1, 0));
  Vector n = s.normal_at(Point(0, 1.70711, -0.70711));
  REQUIRE_THAT(n, Equals(Vector(0, 0.70711, -0.70711)));
}

TEST_CASE("Computing the normal on a transformed sphere", "[Sphere]") {
  Sphere s;
  s.set_transform(scaling(1, 0.5, 1) * rotation_z(PI / 5));
  Vector n = s.normal_at(Point(0, sqrt(2) / 2, -sqrt(2) / 2));
  REQUIRE_THAT(n, Equals(Vector(0, 0.97014, -0.242536)));
}

//------------------------------------------------------------------------------
// Material
//------------------------------------------------------------------------------
TEST_CASE("A sphere has a default material", "[Sphere]") {
  Sphere s;
  const SimpleMaterial& m = dynamic_cast<const SimpleMaterial&>(s.material());
  REQUIRE_THAT(m,
               Equals(dynamic_cast<const SimpleMaterial&>(Material::Default)));
}

TEST_CASE("A sphere may be assigned a material", "[Sphere]") {
  Sphere s;
  SimpleMaterial m;
  m.ambient = 1;
  s.set_material(&m);
  REQUIRE_THAT(dynamic_cast<const SimpleMaterial&>(s.material()), Equals(m));
}

//------------------------------------------------------------------------------
// Glass Sphere
//------------------------------------------------------------------------------
TEST_CASE("A helper for producing a sphere with a glassy material",
          "[Sphere]") {
  Sphere s = glass_sphere;
  REQUIRE_THAT(s.transform(), Equals(Matrix::Identity));
  REQUIRE(s.material().transparency == Approx(1.0));
  REQUIRE(s.material().refractive_index == Approx(1.5));
}

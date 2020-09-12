#pragma once

#include <sstream>

#include "Core/Color.hpp"
#include "Core/Constants.hpp"
#include "Core/Intersection.hpp"
#include "Core/Matrix.hpp"
#include "Core/Point.hpp"
#include "Core/Transformations.hpp"
#include "Core/Vector.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/Material.hpp"
#include "Scene/Objects/Materials/Patterns/Pattern.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "Scene/Scene.hpp"
#include "catch.hpp"

template <class T>
class TupleEquals : public Catch::MatcherBase<T> {
  T expected;

 public:
  TupleEquals(const T& e) : expected{e} {}

  bool match(const T& t) const override {
    return t.vec4[0] == Approx(expected.vec4[0]).margin(EPSILON) &&
           t.vec4[1] == Approx(expected.vec4[1]).margin(EPSILON) &&
           t.vec4[2] == Approx(expected.vec4[2]).margin(EPSILON) &&
           t.vec4[3] == Approx(expected.vec4[3]).margin(EPSILON);
  }

  virtual std::string describe() const override {
    std::ostringstream ss;
    ss << "equals " << expected;
    return ss.str();
  }
};

//------------------------------------------------------------------------------
// Vector
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
  return os;
}

inline TupleEquals<Vector> Equals(const Vector& expected) {
  return TupleEquals<Vector>(expected);
}

//------------------------------------------------------------------------------
// Point
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
  return os;
}

inline TupleEquals<Point> Equals(const Point& expected) {
  return TupleEquals<Point>(expected);
}

//------------------------------------------------------------------------------
// Color
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Color& c) {
  os << "(" << c.r << "," << c.g << "," << c.b << ")";
  return os;
}

inline TupleEquals<Color> Equals(const Color& expected) {
  return TupleEquals<Color>(expected);
}

//------------------------------------------------------------------------------
// Matrix
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  os << "[";
  for (int r = 0; r < 4; ++r) {
    os << "[";
    for (int c = 0; c < 4; ++c) {
      os << m.mat4[r][c];
      os << (c < 3 ? "," : "");
    }
    os << "]" << (r < 3 ? "," : "");
  }
  os << "]";
  return os;
}

class MatrixEquals : public Catch::MatcherBase<Matrix> {
  Matrix expected;

 public:
  MatrixEquals(const Matrix& e) : expected{e} {}

  bool match(const Matrix& m) const override {
    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 4; ++c) {
        if (expected.mat4[r][c] != Approx(m.mat4[r][c]).margin(EPSILON)) {
          return false;
        }
      }
    }
    return true;
  }

  virtual std::string describe() const override {
    std::ostringstream ss;
    ss << "equals " << expected;
    return ss.str();
  }
};

inline MatrixEquals Equals(const Matrix& expected) {
  return MatrixEquals(expected);
}

//------------------------------------------------------------------------------
// Intersection
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Intersection& i) {
  os << "(";
  os << i.t << ", ";
  os << i.object;
  os << ")";
  return os;
}

class IntersectionEquals : public Catch::MatcherBase<Intersection> {
  Intersection expected;

 public:
  IntersectionEquals(const Intersection& e) : expected{e} {}

  bool match(const Intersection& i) const override {
    return i.t == Approx(expected.t).margin(EPSILON) &&
           i.object == expected.object;
  }

  virtual std::string describe() const override {
    std::ostringstream ss;
    ss << "equals " << expected;
    return ss.str();
  }
};

inline IntersectionEquals Equals(const Intersection& expected) {
  return IntersectionEquals(expected);
}

//------------------------------------------------------------------------------
// Material
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const SimpleMaterial& m) {
  os << "(";
  os << m.color << ", ";
  os << m.ambient << ", ";
  os << m.diffuse << ", ";
  os << m.specular << ", ";
  os << m.shininess << ", ";
  os << ")";
  return os;
}

class SimpleMaterialEquals : public Catch::MatcherBase<SimpleMaterial> {
  SimpleMaterial expected;
  TupleEquals<Color> color_matcher;

 public:
  SimpleMaterialEquals(const SimpleMaterial& e)
      : expected{e}, color_matcher{e.color} {}

  bool match(const SimpleMaterial& m) const override {
    if (m.ambient != Approx(expected.ambient)) return false;
    if (m.diffuse != Approx(expected.diffuse)) return false;
    if (m.specular != Approx(expected.specular)) return false;
    if (m.shininess != Approx(expected.shininess)) return false;
    if (!color_matcher.match(m.color)) return false;
    return true;
  }

  virtual std::string describe() const override {
    std::ostringstream ss;
    ss << "equals " << expected;
    return ss.str();
  }
};

inline SimpleMaterialEquals Equals(const SimpleMaterial& expected) {
  return SimpleMaterialEquals(expected);
}

//------------------------------------------------------------------------------
// Scene
//------------------------------------------------------------------------------
inline Light default_light(Point(-10, 10, -10), Color(1, 1, 1));
inline SimpleMaterial default_material_1(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2,
                                         200, 0, 0, 1);
inline Sphere default_sphere_1(Matrix::Identity, default_material_1);
inline SimpleMaterial default_material_2{};
inline Sphere default_sphere_2(scaling(0.5, 0.5, 0.5), default_material_2);
inline Scene default_scene({&default_light},
                           {&default_sphere_1, &default_sphere_2});

inline SimpleMaterial default_glass_material(Color(1, 1, 1), 0.1, 0.9, 0.9, 200,
                                             0, 1, 1.5);
inline Sphere glass_sphere(Matrix::Identity, default_glass_material);

//------------------------------------------------------------------------------
// Pattern
//------------------------------------------------------------------------------
class TestPattern : public Pattern {
 public:
  using Pattern::Pattern;

 public:
  Color color_at(const Point& point) const override {
    return Color(point.x, point.y, point.z);
  }
};

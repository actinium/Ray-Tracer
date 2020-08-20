#pragma once

#include <sstream>

#include "Core/Color.hpp"
#include "Core/Constants.hpp"
#include "Core/Intersection.hpp"
#include "Core/Matrix.hpp"
#include "Core/Point.hpp"
#include "Core/Vector.hpp"
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

#pragma once

#include <sstream>

#include "Core/Vector.hpp"
#include "catch.hpp"

//------------------------------------------------------------------------------
// Vector
//------------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
  return os;
}

class VectorEquals : public Catch::MatcherBase<Vector> {
  Vector expected;

 public:
  VectorEquals(const Vector& e) : expected{e} {}

  bool match(Vector const& v) const override {
    return v.x == Approx(expected.x) && v.y == Approx(expected.y) &&
           v.z == Approx(expected.z) && v.w == Approx(expected.w);
  }

  virtual std::string describe() const override {
    std::ostringstream ss;
    ss << "equals " << expected;
    return ss.str();
  }
};

inline VectorEquals Equals(const Vector& expected) {
  return VectorEquals(expected);
}

//------------------------------------------------------------------------------
// Point
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Matrix
//------------------------------------------------------------------------------

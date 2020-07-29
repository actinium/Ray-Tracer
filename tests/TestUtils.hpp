#pragma once

#include <sstream>

#include "Core/Vector.hpp"
#include "catch.hpp"

template<class T>
class TupleEquals : public Catch::MatcherBase<T> {
  T expected;

 public:
  TupleEquals(const T& e) : expected{e} {}

  bool match(const T& t) const override {
    return t.x == Approx(expected.x) && t.y == Approx(expected.y) &&
           t.z == Approx(expected.z) && t.w == Approx(expected.w);
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

//------------------------------------------------------------------------------
// Matrix
//------------------------------------------------------------------------------

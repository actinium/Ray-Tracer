#pragma once

#include "Matrix.hpp"
#include "Point.hpp"
#include "Vector.hpp"

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
Vector operator+(const Vector& v1, const Vector& v2);
Point operator+(const Point& p, const Vector& v);

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator-(const Point& p1, const Point& p2);
Point operator-(const Point& p, const Vector& v);

//------------------------------------------------------------------------------
// Negation
//------------------------------------------------------------------------------
Vector operator-(const Vector& v);
Point operator-(const Point& p);

//------------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------------
Matrix operator*(const Matrix& m1, const Matrix& m2);
Vector operator*(const Matrix& m, const Vector& v);
Point operator*(const Matrix& m, const Point& p);

Vector cross(const Vector& v1, const Vector& v2);
double dot(const Vector& v1, const Vector& v2);

Vector operator*(double s, const Vector& v);
Vector operator*(const Vector& v, double s);

//------------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------------
Vector operator/(double s, const Vector& v);
Vector operator/(const Vector& v, double s);

//------------------------------------------------------------------------------
// Magnitude
//------------------------------------------------------------------------------
double magnitude(const Vector& v);
Vector normalize(const Vector& v);

//------------------------------------------------------------------------------
// Reflection
//------------------------------------------------------------------------------
Vector reflect(const Vector& v, const Vector& n);

//------------------------------------------------------------------------------
// Transposition
//------------------------------------------------------------------------------
Matrix transpose(const Matrix& m);

//------------------------------------------------------------------------------
// Inversion
//------------------------------------------------------------------------------
Matrix inverse(const Matrix& m);

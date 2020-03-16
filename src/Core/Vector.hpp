#pragma once

class Vector {
 public:
  double& x = v[0];
  double& y = v[1];
  double& z = v[2];
  double& w = v[3];

 private:
  alignas(32) double v[4];
};

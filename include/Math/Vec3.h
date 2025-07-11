#pragma once

namespace Math {

  class Vec3 {
  public:
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    static Vec3 zero() { return {0, 0, 0}; }
  };

} // namespace Math

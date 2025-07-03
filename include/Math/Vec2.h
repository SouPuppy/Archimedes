#pragma once

namespace Math {
  class Vec2 {
  public:
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    static Vec2 zero() { return {0, 0}; }
    Vec2 operator+(const Vec2& b) const { return {x + b.x, y + b.y}; }
  };
} // namespace Math

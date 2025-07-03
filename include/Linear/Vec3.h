#ifndef VEC3_H
#define VEC3_H

namespace Linear {

class Vec3 {
    float x, y, z;
public:
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

} // Linear

#endif //VEC3_H

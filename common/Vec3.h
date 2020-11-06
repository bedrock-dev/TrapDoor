//
// Created by xhy on 2020/10/22.
//

#ifndef LIBMCBEMOD_VEC3_H
#define LIBMCBEMOD_VEC3_H

#include <string>

struct BlockPos;

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() = default;

    explicit Vec3(int _x);

    explicit Vec3(float _x);

    Vec3(int _x, int _y, int _z) : x((float) _x), y((float) _y), z((float) _z) {}

    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    bool operator==(const Vec3 &v) const;

    bool operator!=(const Vec3 &v) const;

    float distanceTo(const Vec3 &vec3) const;

    std::string toString() const;
    BlockPos toBlockPos() const;

};


#endif //LIBMCBEMOD_VEC3_H

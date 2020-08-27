//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_VEC3_H
#define TRAPDOOR_VEC3_H

#include <iostream>

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() = default;

    explicit Vec3(int _x) : Vec3(_x, _x, _x) {}

    explicit Vec3(float _x) : Vec3(_x, _x, _x) {}

    Vec3(int _x, int _y, int _z) : x((float) _x), y((float) _y), z((float) _z) {}

    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    bool operator==(const Vec3 &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const Vec3 &v) const {
        return x != v.x || y != v.y || z != v.z;
    }

    float distanceTo(const Vec3 &vec3) const {
        return (vec3.x - x) * (vec3.x - x) +
               (vec3.y - y) * (vec3.y - y) +
               (vec3.z - z) * (vec3.z - z);
    }

};


#endif //TRAPDOOR_VEC3_H

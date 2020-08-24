//
// Created by xhy on 2020/8/24.
//
#ifndef TRAPDOOR_AABB_H
#define TRAPDOOR_AABB_H

#include "Vec3.h"

struct AABB {
    Vec3 p1{};
    Vec3 p2{};
    AABB(Vec3 _p1, Vec3 _p2) {
        p1.x = _p1.x;
        p1.y = _p1.y;
        p1.z = _p1.z;
        p2.x = _p2.x;
        p2.y = _p2.y;
        p2.z = _p2.z;
    }



};

#endif //TRAPDOOR_AABB_H

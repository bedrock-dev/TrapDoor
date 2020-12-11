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
        p1 = _p1;
        p2 = _p2;
    }
};

#endif //TRAPDOOR_AABB_H

//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_BLOCKPOS_H
#define TRAPDOOR_BLOCKPOS_H

#include <iostream>
#include "Vec3.h"

struct BlockPos {
    int x;
    int y;
    int z;

    BlockPos() = default;

    BlockPos(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

    explicit BlockPos(int x) : BlockPos(x, x, x) {}

    explicit BlockPos(float x) : BlockPos(x, x, x) {}

    BlockPos(float _x, float _y, float _z) : x((int) _x), y((int) _y), z((int) _z) {}

    bool operator==(const BlockPos &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const BlockPos &v) const {
        return x != v.x || y != v.y || z != v.z;
    }

    float distanceTo(const BlockPos &blockPos) const {
        return (float) ((blockPos.x - x) * (blockPos.x - x) +
                        (blockPos.y - y) * (blockPos.y - y) +
                        (blockPos.z - z) * (blockPos.z - z));
    }

    friend std::ostream &operator<<(std::ostream &os, const BlockPos &vec3) {
        os << "[" << vec3.x << "," << vec3.y << "," << vec3.z << "]";
        return os;
    }

    Vec3 toVec3() const {
        return {x, y, z};
    }


};

#endif //TRAPDOOR_BLOCKPOS_H

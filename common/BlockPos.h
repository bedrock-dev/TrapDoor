//
// Created by xhy on 2020/10/22.
//

#ifndef LIBMCBEMOD_BLOCKPOS_H
#define LIBMCBEMOD_BLOCKPOS_H

#include "Vec3.h"
#include <iostream>
#include <vector>


struct ChunkPos {
    int x = 0;
    int z = 0;

    ChunkPos(int _x, int _z) : x(_x), z(_z) {}

    std::string toString() const;

    bool isSlimeChunk() const;
};

struct BlockPos {
    int x = 0;
    int y = 0;
    int z = 0;

    BlockPos() = default;

    BlockPos(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

    explicit BlockPos(int x) : BlockPos(x, x, x) {}

    explicit BlockPos(float x) : BlockPos(x, x, x) {}

    BlockPos(float _x, float _y, float _z) : x((int) _x), y((int) _y), z((int) _z) {}

    bool operator==(const BlockPos &v) const;

    bool operator!=(const BlockPos &v) const;

    float distanceTo(const BlockPos &blockPos) const;

    friend std::ostream &operator<<(std::ostream &os, const BlockPos &vec3);

    Vec3 toVec3() const;

    std::string toString() const;

    std::vector<BlockPos> getNeighbourPos();

    std::vector<BlockPos> getPlainNeighbourPos();

    ChunkPos toChunkPos() const;

    ChunkPos InChunkOffset() const;


    bool operator<(const BlockPos &rhs) const;
};


#endif //LIBMCBEMOD_BLOCKPOS_H

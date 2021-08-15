//
// Created by xhy on 2020/10/22.
//

#ifndef LIBMCBEMOD_BLOCKPOS_H
#define LIBMCBEMOD_BLOCKPOS_H

#include <iostream>
#include <vector>

namespace trapdoor {
    class BlockPos;

    class Vec3;

    enum FACING {
        NEG_Y = 0,
        POS_Y = 1,
        NEG_Z = 2,
        POS_Z = 3,
        NEG_X = 4,
        POS_X = 5,
    };

    bool facingIsPos(FACING facing);

    bool facingIsNeg(FACING facing);

    bool facingIsX(FACING facing);

    bool facingIsY(FACING facing);

    bool facingIsZ(FACING facing);

    FACING invFacing(FACING facing);

    std::string facingToString(FACING facing);

    std::string facingToDirString(FACING facing);

    BlockPos facingToBlockPos(FACING facing);

    struct BlockPos2 {
        int x = 0;
        int z = 0;

        BlockPos2(int _x, int _z) : x(_x), z(_z) {}

        std::string toString() const;

        bool isSlimeChunk() const;

        bool operator<(const BlockPos2 &rhs) const;
    };

    typedef BlockPos2 ChunkPos;

    class BlockPos {
       public:
        int x = 0;
        int y = 0;
        int z = 0;

        BlockPos() = default;

        BlockPos(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

        explicit BlockPos(int x) : BlockPos(x, x, x) {}

        explicit BlockPos(float x) : BlockPos(x, x, x) {}

        BlockPos(float _x, float _y, float _z)
            : x((int)_x), y((int)_y), z((int)_z) {}

        bool operator==(const BlockPos &v) const;

        bool operator!=(const BlockPos &v) const;

        float distanceTo(const BlockPos &blockPos) const;

        friend std::ostream &operator<<(std::ostream &os, const BlockPos &vec3);

        Vec3 toVec3() const;

        std::string toString() const;

        std::vector<BlockPos> getNeighbourPos();

        std::vector<BlockPos> getPlainNeighbourPos();

        BlockPos2 toChunkPos() const;

        BlockPos2 InChunkOffset() const;

        int operator*(const BlockPos &pos) const;

        BlockPos operator+(const BlockPos &pos) const;

        bool operator<(const BlockPos &rhs) const;
    };

}  // namespace trapdoor
#endif  // LIBMCBEMOD_BLOCKPOS_H

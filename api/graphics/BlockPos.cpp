//
// Created by xhy on 2020/10/22.
//

#include "BlockPos.h"

#include <random>
#include <string>

#include "Vec3.h"

namespace trapdoor {
    bool BlockPos::operator==(const BlockPos &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool BlockPos::operator!=(const BlockPos &v) const {
        return x != v.x || y != v.y || z != v.z;
    }

    float BlockPos::distanceTo(const BlockPos &blockPos) const {
        return (float)sqrt((blockPos.x - x) * (blockPos.x - x) +
                           (blockPos.y - y) * (blockPos.y - y) +
                           (blockPos.z - z) * (blockPos.z - z));
    }

    std::ostream &operator<<(std::ostream &os, const BlockPos &vec3) {
        os << "[" << vec3.x << "," << vec3.y << "," << vec3.z << "]";
        return os;
    }

    Vec3 BlockPos::toVec3() const { return {x, y, z}; }

    std::string BlockPos::toString() const {
        return "[" + std::to_string(x) + "," + std::to_string(y) + "," +
               std::to_string(z) + "]";
    }

    std::vector<BlockPos> BlockPos::getNeighbourPos() {
        return {{x + 1, y, z}, {x - 1, y, z}, {x, y + 1, z},
                {x, y - 1, z}, {x, y, z + 1}, {x, y, z - 1}};
    }

    std::vector<BlockPos> BlockPos::getPlainNeighbourPos() {
        return {{x + 1, y, z}, {x - 1, y, z}, {x, y, z + 1}, {x, y, z - 1}};
    }

    BlockPos2 BlockPos::InChunkOffset() const {
        auto newX = x % 16;
        auto newZ = z % 16;
        if (newX < 0) newX += 16;
        if (newZ < 0) newZ += 16;
        return {newX, newZ};
    }

    BlockPos2 BlockPos::toChunkPos() const {
        auto cx = x < 0 ? x - 15 : x;
        auto cz = z < 0 ? z - 15 : z;
        return {cx / 16, cz / 16};
    }

    bool BlockPos::operator<(const BlockPos &rhs) const {
        if (x < rhs.x) return true;
        if (rhs.x < x) return false;
        if (y < rhs.y) return true;
        if (rhs.y < y) return false;
        return z < rhs.z;
    }

    int BlockPos::operator*(const BlockPos &pos) const {
        return this->x * pos.x + this->y * pos.y + this->z * pos.z;
    }

    BlockPos BlockPos::operator+(const BlockPos &pos) const {
        return {x + pos.x, y + pos.y, z + pos.z};
    }

    std::string BlockPos2::toString() const {
        return "[" + std::to_string(x) + "," + std::to_string(z) + "]";
    }

    bool BlockPos2::isSlimeChunk() const {
        auto seed = (x * 0x1f1f1f1fu) ^ (uint32_t)z;
        std::mt19937 mt(seed);
        return mt() % 10 == 0;
    }

    bool BlockPos2::operator<(const BlockPos2 &rhs) const {
        if (x < rhs.x) return true;
        if (rhs.x < x) return false;
        return z < rhs.z;
    }

    std::string facingToString(FACING facing) {
        switch (facing) {
            case FACING::POS_X:
                return "+x";
            case FACING::NEG_X:
                return "-x";
            case FACING::POS_Y:
                return "+y";
            case FACING::POS_Z:
                return "+z";
            case FACING::NEG_Y:
                return "-y";
            case FACING::NEG_Z:
                return "-z";
            default:
                return "unknown";
        }
    }

    std::string facingToDirString(FACING facing) {
        switch (facing) {
            case FACING::POS_X:
                return "west";
            case FACING::NEG_X:
                return "east";
            case FACING::POS_Y:
                return "up";
            case FACING::POS_Z:
                return "south";
            case FACING::NEG_Y:
                return "down";
            case FACING::NEG_Z:
                return "north";
            default:
                return "unknown";
        }
    }

    BlockPos facingToBlockPos(FACING facing) {
        switch (facing) {
            case FACING::NEG_Y:
                return {0, -1, 0};
            case FACING::POS_Y:
                return {0, 1, 0};
            case FACING::NEG_Z:
                return {0, 0, -1};
            case FACING::POS_Z:
                return {0, 0, 1};
            case FACING::NEG_X:
                return {-1, 0, 0};
            case FACING::POS_X:
                return {1, 0, 0};
        }
        return {0, 0, 0};
    }

    bool facingIsPos(FACING facing) {
        return facing == FACING::POS_X || facing == FACING::POS_Y ||
               facing == FACING::POS_Z;
    }

    bool facingIsNeg(FACING facing) {
        return facing == FACING::NEG_X || facing == FACING::NEG_Y ||
               facing == FACING::NEG_Z;
    }

    bool facingIsX(FACING facing) {
        return facing == FACING::POS_X || facing == FACING::NEG_X;
    }

    bool facingIsY(FACING facing) {
        return facing == FACING::POS_Y || facing == FACING::NEG_Y;
    }

    bool facingIsZ(FACING facing) {
        return facing == FACING::POS_Z || facing == FACING::NEG_Z;
    }

    FACING invFacing(FACING facing) {
        switch (facing) {
            case FACING::NEG_Y:
                return FACING::POS_Y;
            case FACING::POS_Y:
                return FACING::NEG_Y;
            case FACING::NEG_Z:
                return FACING::POS_Z;
            case FACING::POS_Z:
                return FACING::NEG_Z;
            case FACING::NEG_X:
                return FACING::POS_X;
            case FACING::POS_X:
                return FACING::NEG_X;
            default:
                return FACING::POS_X;
        }
    }
}  // namespace trapdoor
typedef trapdoor::BlockPos BlockPos;
typedef trapdoor::BlockPos2 BlockPos2;

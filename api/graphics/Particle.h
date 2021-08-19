//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_PARTICLE_H
#define TRAPDOOR_PARTICLE_H

#include <string>

#include "AABB.h"
namespace trapdoor {

    enum class GRAPHIC_COLOR {
        WHITE = 0,
        RED = 1,
        YELLOW = 2,
        BLUE = 3,
        GREEN = 4
    };
    void drawLine(const Vec3 &originPoint, FACING direction, float length,
                  GRAPHIC_COLOR color, int dimType = 0);

    void drawPoint(const Vec3 &point, GRAPHIC_COLOR color, int dimType = 0);

    void spawnParticle(Vec3 p, std::string &type, int dimType = 0);

    void spawnRectangleParticle(const AABB &aabb, GRAPHIC_COLOR color,
                                int dimType = 0);

    void spawnChunkSurfaceParticle(const ChunkPos &pos, int dimID);

    void spawnSlimeChunkParticle(const ChunkPos &pos);

    void spawnLineParticle(const Vec3 &p, FACING facing, float length,
                           GRAPHIC_COLOR color, int dimType = 0);
}  // namespace trapdoor

typedef trapdoor::GRAPHIC_COLOR GRAPH_COLOR;

#endif  // TRAPDOOR_PARTICLE_H

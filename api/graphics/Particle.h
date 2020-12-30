//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_PARTICLE_H
#define TRAPDOOR_PARTICLE_H

#include <string>

#include "Graphics.h"
#include "AABB.h"

namespace trapdoor {
    void spawnParticle(Vec3 p, std::string &type, int dimType = 0);

    void spawnRectangleParticle(const AABB &aabb, GRAPHIC_COLOR color, int dimType = 0);

}
#endif    // TRAPDOOR_PARTICLE_H

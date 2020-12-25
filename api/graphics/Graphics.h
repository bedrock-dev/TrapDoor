//
// Created by xhy on 2020/12/12.
//

#ifndef TRAPDOOR_GRAPHICS_H
#define TRAPDOOR_GRAPHICS_H

//#include "Particle.h"
#include "BlockPos.h"
#include <vector>
#include <map>

namespace trapdoor {
    enum class COLOR {
        WHITE,
        RED,
        YELLOW,
        BLUE,
        GREEN
    };

    void drawLine(const Vec3 &originPoint, FACING direction, float length, COLOR color);

}


#endif //TRAPDOOR_GRAPHICS_H

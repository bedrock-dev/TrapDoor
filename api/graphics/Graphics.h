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
    enum class GRAPHIC_COLOR {
        WHITE = 0,
        RED = 1,
        YELLOW = 2,
        BLUE = 3,
        GREEN = 4
    };

    void drawLine(const Vec3 &originPoint, FACING direction, float length, GRAPHIC_COLOR color, int dimType = 0);
}
typedef trapdoor::GRAPHIC_COLOR GRAPH_COLOR;

#endif //TRAPDOOR_GRAPHICS_H

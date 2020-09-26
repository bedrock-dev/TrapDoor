//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MATHTOOL_H
#define TRAPDOOR_MATHTOOL_H

#include "common/Vec3.h"
#include "common/BlockPos.h"
#include <cmath>
#include <vector>

namespace math {

    enum class FACING {
        POS_X,
        NEG_X,
        POS_Y,
        NEG_Y,
        POS_Z,
        NEG_Z
    };

    /*  ________
     * | \    /|
     * |  \  / |
     * |  /  \ |
     * | /____\|
     */
    struct point_pos {
        BlockPos pos;
        FACING facing;
        FACING offset;
        point_pos(int x, int y, int z, FACING fac, FACING off) : pos(x, y, z), facing(fac), offset(off) {}

    };

    double distance(Vec3 p1, Vec3 p2, bool useManhattan = false, bool withY = true);

    std::vector<float> cut(float begin, float end, int num);

    std::vector<point_pos> getViewPosList(Vec3 pos, Vec3 viewVector, float maxPos);

}
#endif //TRAPDOOR_MATHTOOL_H

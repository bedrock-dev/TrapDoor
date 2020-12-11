//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MATHTOOL_H
#define TRAPDOOR_MATHTOOL_H

#include "graphics/Vec3.h"
#include "graphics/BlockPos.h"
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

    double distance(Vec3 p1, Vec3 p2, bool useManhattan = false, bool withY = true);

    std::vector<float> cut(float begin, float end, int num);

}
#endif //TRAPDOOR_MATHTOOL_H

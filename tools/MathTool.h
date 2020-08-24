//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MATHTOOL_H
#define TRAPDOOR_MATHTOOL_H

#include "common/Vec3.h"
#include "cmath"

namespace math {
    double distance(Vec3 p1, Vec3 p2, bool useManhattan = false, bool withY = true) {
        auto dx = fabs(p2.x - p1.x);
        auto dy = withY ? fabs(p2.y - p1.y) : 0;
        auto dz = fabs(p2.z - p1.z);
        return useManhattan ? dx + dy + dz : sqrt(dx * dx + dy * dy + dz * dz);
    }

    std::vector<float> cut(float begin, float end, int num) {
        float distance = (end - begin) / (float) num;
        std::vector<float> result;
        result.reserve(num);
        for (int i = 0; i <= num; ++i)
            result.emplace_back(begin + (float) i * distance);
        return result;
    }
}
#endif //TRAPDOOR_MATHTOOL_H

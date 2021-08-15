//
// Created by xhy on 2020/11/13.
//

#include "Dimension.h"

#include <cstdio>

#include "Offset.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    //打印维度上限，目前没屌用
    void Dimension::printBaseTypeLimit() {
        // from Spawner::_popCapAllows
        char *dim = reinterpret_cast<char *>(this);
        auto *surface = (float *)(dim + 80);
        auto *underground = (float *)(dim + 108);
        for (int i = 0; i < 7; i++) {
            printf("%.3f    %.3f\n", surface[i], underground[i]);
        }
    }

    bool Dimension::isRedstoneTick() {
        //为1是红石刻2是非红石刻
        return *((uint32_t *)this + off::DIMENSION_IS_RS_TICK) == 1;
    }
}  // namespace trapdoor

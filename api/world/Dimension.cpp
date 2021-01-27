//
// Created by xhy on 2020/11/13.
//

#include "Dimension.h"
#include <cstdio>
#include "tools/DirtyLogger.h"

namespace trapdoor {
//打印维度上限，目前没屌用
    void Dimension::printBaseTypeLimit() {
        //from Spawner::_popCapAllows
        char *dim = reinterpret_cast<char *>(this);
        auto *surface = (float *) (dim + 80);
        auto *underground = (float *) (dim + 108);
        for (int i = 0; i < 7; i++) {
            printf("%.3f    %.3f\n", surface[i], underground[i]);
        }
    }

    CircuitSceneGraph *Dimension::getGraph() {
        //这种代码真的写的人瘆得慌
        //from Dimension::tickRedstone(Dimension *this)
        uint64_t *circuitSystem = reinterpret_cast<uint64_t *>(this) + 35;
        return reinterpret_cast<CircuitSceneGraph *> (*circuitSystem + 8);
    }
}

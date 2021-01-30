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
        uint64_t *circuitSystem = reinterpret_cast<uint64_t *>(this) + 33;
        return reinterpret_cast<CircuitSceneGraph *> (*circuitSystem + 8);
    }

    bool Dimension::isRedstoneTick() {
        //为1是红石刻2是非红石刻
        return *((uint32_t *) this + 69) == 1;
        //  auto v2 = *((uint32_t *) this + 68); //恒定为2,也就是多少gt才过一个红石刻
        // printf("%d %d\n", v1, v2);
    }
}

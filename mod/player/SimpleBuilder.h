//
// Created by xhy on 2021/1/5.
//

#ifndef MOD_SIMPLEBUILDER_H
#define MOD_SIMPLEBUILDER_H

#include "entity/Actor.h"
#include "block/BlockSource.h"

namespace mod {
    class SimpleBuilder {
        size_t maxCircleRadius = 32;
        bool enable = true;

    public:
        void buildSphere(trapdoor::Actor *player, size_t size, bool hollow) const;

        void buildCircle(trapdoor::Actor *player, size_t size, bool hollow) const;
    };
}

#endif //MOD_SIMPLEBUILDER_H

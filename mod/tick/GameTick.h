//
// Created by xhy on 2020/10/29.
//

#ifndef TRAPDOOR_GAMETICK_H
#define TRAPDOOR_GAMETICK_H


#include "SimpleProfiler.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "village/Village.h"
#include <vector>
#include <chrono>
#include "tools/Message.h"
#include "entity/Actor.h"

namespace mod::tick {
    enum WorldTickStatus {
        Frozen,
        Normal,
        Slow,
        Forward,
        Wrap
    };

    WorldTickStatus getTickStatus();

    void freezeTick();

    void resetTick();

    void wrapTick(size_t wrapSpeed);

    void forwardTick(size_t tickNum);

    void slowTick(size_t slowSpeed);

    void profileWorld(trapdoor::Actor *player);

    void profileEntities(trapdoor::Actor *player);

    void queryStatus(trapdoor::Actor *player);

    void mspt();
}

#endif //TRAPDOOR_GAMETICK_H

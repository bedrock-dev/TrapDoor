//
// Created by xhy on 2020/10/29.
//

#ifndef TRAPDOOR_GAMETICK_H
#define TRAPDOOR_GAMETICK_H

#include <chrono>

typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END auto elapsed = timer_clock::now() - start; long long timeReslut =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

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

    void mspt();
}

#endif //TRAPDOOR_GAMETICK_H

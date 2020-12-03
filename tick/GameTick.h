//
// Created by xhy on 2020/10/29.
//

#ifndef TRAPDOOR_GAMETICK_H
#define TRAPDOOR_GAMETICK_H

#include <chrono>

typedef std::chrono::high_resolution_clock timer_clock;
typedef uint64_t Tick;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END auto elapsed = timer_clock::now() - start; long long timeReslut =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();


#include "common/Trapdoor.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "village/Village.h"
#include <vector>
#include <chrono>
#include "tools/Message.h"

namespace tick {
    enum WorldTickStatus {
        Frozen,
        Normal,
        Slow,
        Forward,
        Wrap
    };

    extern WorldTickStatus tickStatus;
    extern size_t wrapSpeed;
    extern WorldTickStatus lastTickStats;
    extern int SlowDownTimes;  //slow down time
    extern int slowDownCounter; //slow down counter
    extern int forwardTickNum; //forward tick num
    extern bool isProfiling;

    void freezeTick();

    void resetTick();

    void wrapTick(size_t wrapSpeed);

    void forwardTick(size_t tickNum);

    void slowTick(size_t slowSpeed);

    void profileWorld(Actor *player);

    void sendProfileInfo();

    void resetProfileCounter();

    void mspt();
}


#endif //TRAPDOOR_GAMETICK_H

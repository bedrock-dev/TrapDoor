#pragma once

#include "common/Common.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "village/Village.h"
#include <vector>
#include <chrono>
#include "tools/Message.h"

using namespace SymHook;
typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END auto elapsed = timer_clock::now() - start; long long timeReslut =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

enum class TickStatus {
    Frozen,
    Normal,
    Slow,
    Forward
};


namespace tick {
    extern TickStatus tickStatus;

    void extraTickTask();

    void freezeWorld();

    void resetWorld();

    void slowWorld(int times);

    void forwardWorld(int tickNum);


    void profileWorld();

    void resetProfileCounter();

    void calProfile();
}

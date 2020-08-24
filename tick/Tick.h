#pragma once

#include "common/Common.h"
#include "lib/pch.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "commands/Shell.h"
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

TickStatus tickStatus = TickStatus::Normal;

namespace tick {
    //profile
    const int TOTAL_PROFILE_ROUND = 100;
    bool isProfiling = false;
    int currentProfileRound = 0;

    long long redstoneUpdateTime = 0;
    long long playerTickTime = 0;
    long long levelTickTime = 0;
    long long dimTickTime = 0;
    long long chunkTickTime = 0;
    long long randTickTime = 0;
    long long blockEntityTickTime = 0;
    long long spawnerTickTime = 0;

    //slow
    int SlowDownTimes = 1;  //slow down time
    int slowDownCounter = 0; //slow down counter
    int forwardTickNum = 0; //forward tick num


    void extraTickTask() {
        //here are the tasks;
        //task in normal status(heavy work)
        if (tickStatus == TickStatus::Normal) {
           village::villageTask();
        }
        //task in any status (light work)
        if (mobSpawnCounterStart)++mobTickCounter;
    }

    void freezeWorld() {
        if (tickStatus == TickStatus::Normal) {
            tickStatus = TickStatus::Frozen;
            forwardTickNum = 0;
            gamePrintf("the world has been frozen\n");
        } else {
            gamePrintf("this command must be run in normal status\n");
        }
    }

    void resetWorld() {
        if (forwardTickNum > 0) {
            gamePrintf("forwarding, try later\n");
        } else {
            tickStatus = TickStatus::Normal;
            SlowDownTimes = 0;
            gamePrintf("reset tick status\n");
        }
    }

    void slowWorld(int times) {
        if (tickStatus == TickStatus::Normal) {
            gamePrintf("world has slowed\n");
            tickStatus = TickStatus::Slow;
            SlowDownTimes = times;
        } else {
            gamePrintf("this command must be run at normal status\n");
        }
    }

    void forwardWorld(int tickNum) {
        if (tickStatus == TickStatus::Frozen) {
            forwardTickNum = tickNum;
            tickStatus = TickStatus::Forward;
        } else {
            error("this command must be run at frozen status\n");
        }
    }


    void profileWorld() {
        info("start profiling...");
        isProfiling = true;
        currentProfileRound = TOTAL_PROFILE_ROUND;
    }

    void resetProfileCounter() {
        redstoneUpdateTime = 0;
        levelTickTime = 0;
        dimTickTime = 0;
        playerTickTime = 0;
        chunkTickTime = 0;
        randTickTime = 0;
        blockEntityTickTime = 0;
        spawnerTickTime = 0;
    }

    void calProfile() {
        gamePrintf("mpst:            §2%.3f\n" \
               "§rredstone:             §2%.3f\n" \
               "§rlevel:                §2%.3f\n" \
               "§rchunk & village:      §2%.3f\n" \
               "§rplayer:               §2%.3f\n" \
               "§rchunk tick:           §2%.3f\n" \
               "§random tick & env:     §2%.3f\n" \
               "§rblockEntities:   §2%.3f\n" \
               "§r(de)spawn:       §2%.3f",
                   (double) redstoneUpdateTime / 90000 + (double) levelTickTime / 100000,
                   (double) redstoneUpdateTime / 90000,
                   (double) levelTickTime / 100000,
                   (double) dimTickTime / 100000,
                   (double) playerTickTime / 100000,
                   (double) chunkTickTime / 100000,
                   (double) randTickTime / 100000,
                   (double) blockEntityTickTime / 100000,
                   (double) spawnerTickTime / 100000
        );
        resetProfileCounter();
    }
}

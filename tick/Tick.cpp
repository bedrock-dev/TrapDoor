//
// Created by xhy on 2020/8/25.
//

#include "Tick.h"

using namespace SymHook;

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
    TickStatus tickStatus = TickStatus::Normal;

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
        dbg("freeze world");
        if (tickStatus == TickStatus::Normal) {
            tickStatus = TickStatus::Frozen;
            forwardTickNum = 0;
            info("the world has been frozen\n");
        } else {
            warning("this command must be run in normal status\n");
        }
    }

    void resetWorld() {
        if (forwardTickNum > 0) {
            warning("forwarding, try later\n");
        } else {
            tickStatus = TickStatus::Normal;
            SlowDownTimes = 0;
            warning("reset tick status\n");
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

    void slowWorld(int times) {
        if (tickStatus == TickStatus::Normal) {
            gamePrintf("world has slowed\n");
            tickStatus = TickStatus::Slow;
            SlowDownTimes = times;
        } else {
            gamePrintf("this command must be run at normal status\n");
        }
    }
}

//Level::tick function, the top tick function(except redstone update)
THook(void,
      MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ,
      void *l) {
    if (!globalLevel) { globalLevel = l; }
    //normal task
    if (tick::tickStatus == TickStatus::Normal) {
        if (tick::isProfiling) {
            TIMER_START
            original(l);
            tick::extraTickTask();
            TIMER_END
            tick::levelTickTime += timeReslut;
            tick::currentProfileRound--;
            if (tick::currentProfileRound == 0) {
                tick::isProfiling = false;
                tick::calProfile();
            }
        } else {
            original(l);
            tick::extraTickTask();
        }
        //forward ticks
    } else if (tick::tickStatus == TickStatus::Forward) {
        gamePrintf("forward start ,please wait\n");
        for (int i = 0; i < tick::forwardTickNum; i++) {
            //先调用level::tick
            original(l);
            tick::extraTickTask();

            //call Dimension::tickRedstone;
            SYM_CALL(
                    void(*)(void * ),
                    MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ,
                    globalDimension
            );
        }
        gamePrintf("end forward\n");
        tick::forwardTickNum = 0;
        tick::tickStatus = TickStatus::Frozen;
    } else if (tick::tickStatus == TickStatus::Slow) {
        if (tick::slowDownCounter % tick::SlowDownTimes == 0) {
            original(l);
            tick::extraTickTask();
        }
        tick::slowDownCounter = (tick::slowDownCounter + 1) % tick::SlowDownTimes;
    }
}

//ServerPlayer::tickWorld
THook(
        void,
        MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z,
        void *p,
        void * tick
) {
    if (!globalPlayer) {
        dbg("player init");
        globalPlayer = p;
    }
    //如果是一般状态
    if (tick::isProfiling) {
        TIMER_START
        original(p, tick);
        TIMER_END
        tick::playerTickTime += timeReslut;
    } else {
        original(p, tick);
    }
}

//Dimension::tick
THook(
        void,
        MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ,
        void * dim
) {
    if (!globalDimension)globalDimension = dim;
    if (tick::isProfiling) {
        TIMER_START
        original(dim);
        TIMER_END
        tick::dimTickTime += timeReslut;
    } else {
        original(dim);
    }

}
//LevelChunk::tick
THook(
        void,
        MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z,
        void *levelChunk,
        void *blockSource,
        void * tick
) {
    if (!globalBlockSource)globalBlockSource = blockSource;
    if (tick::isProfiling) {
        TIMER_START
        original(levelChunk, blockSource, tick);
        TIMER_END
        tick::chunkTickTime += timeReslut;
    } else {
        original(levelChunk, blockSource, tick);
    }
}

//LevelChunk::tickBlocks
THook(
        void,
        MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z,
        void *levelChunk,
        void *blockSource,
        INT64 a3,
        int a4
) {

    if (tick::isProfiling) {
        TIMER_START
        original(levelChunk, blockSource, a3, a4);
        TIMER_END
        tick::randTickTime += timeReslut;
    } else {
        original(levelChunk, blockSource, a3, a4);
    }

}


//LevelChunk::tickEntities
THook(
        void,
        MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z,
        void *levelChunk,
        void * blockSource
) {

    if (tick::isProfiling) {
        TIMER_START
        original(levelChunk, blockSource);
        TIMER_END
        tick::blockEntityTickTime += timeReslut;
    } else {
        original(levelChunk, blockSource);
    }
}

//mob spawn Spawner::tick
THook(
        void,
        MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEBVLevelChunkB3AAAA1Z,
        void *swr,
        void *blockSource,
        void * chunk
) {
    if (!globalSpawner)globalSpawner = swr;
    if (tick::isProfiling) {
        TIMER_START
        original(swr, blockSource, chunk);
        TIMER_END
        tick::spawnerTickTime += timeReslut;
    } else {
        original(swr, blockSource, chunk);
    }

}

//BlockTickingQueue::pendingTicks
//the server will crash if hook this function
//THook(
//        void,
//        MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z,
//        void *queue,
//        void *source,
//        int flag,
//        bool a1
//) {
//    original(queue, source, flag, a1);
//
//}

//Dimension::tick
THook(
        void,
        MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ,
        void * dim
) {
    if (tick::tickStatus == TickStatus::Normal) {
        if (tick::isProfiling) {
            TIMER_START
            original(dim);
            TIMER_END
            tick::redstoneUpdateTime += timeReslut;
        } else {
            original(dim);
        }
    }

    if (tick::tickStatus == TickStatus::Forward) {
        original(dim);
    } else if (tick::tickStatus == TickStatus::Slow) {
        if (tick::slowDownCounter % tick::SlowDownTimes == 0) {
            original(dim);
        }
    }
}

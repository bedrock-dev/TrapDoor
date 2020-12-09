//
// Created by xhy on 2020/10/29.
//

#include "GameTick.h"
#include "level/Level.h"
#include "block/Hopper.h"
#include "commands/Command.h"

using namespace SymHook;


namespace tick {

    WorldTickStatus tickStatus = WorldTickStatus::Normal;
    WorldTickStatus lastTickStats = WorldTickStatus::Normal;
    size_t wrapSpeed = 1;
    int SlowDownTimes = 1;  //slow down time
    int slowDownCounter = 0; //slow down counter
    int forwardTickNum = 0; //forward tick num
    bool isProfiling = false;
    bool isMSPTing = false;
    int currentProfileRound = 0;

    long long redstoneTickTime = 0;
    long long playerTickTime = 0;
    long long levelTickTime = 0;
    long long dimTickTime = 0;
    long long chunkTickTime = 0;
    long long randTickTime = 0;
    long long blockEntityTickTime = 0;
    long long spawnerTickTime = 0;

    void freezeTick() {
        if (tickStatus == WorldTickStatus::Normal) {
            // info("world has frozen");
            if (tickStatus != WorldTickStatus::Frozen) {
                tickStatus = WorldTickStatus::Frozen;
                L_DEBUG("freeze world");
                broadcastMsg("world has frozen!");
            } else {
                broadcastMsg("it's in frozen state now");
            }
        }
    }

    void resetTick() {
        if (tickStatus != WorldTickStatus::Normal) {
            tickStatus = WorldTickStatus::Normal;
            L_DEBUG("reset world");
        }
        broadcastMsg("world has reset to normal status");
    }

    void wrapTick(size_t speed) {
        if (tickStatus == WorldTickStatus::Normal) {
            broadcastMsg("world begin warp");
            tickStatus = WorldTickStatus::Wrap;
            L_DEBUG("begin wrap world %d", speed);
            wrapSpeed = speed;
        } else {
            broadcastMsg("this command can only be run in normal mode");
        }
    }

    void forwardTick(size_t tickNum) {
        if (tickStatus == WorldTickStatus::Frozen || tickStatus == WorldTickStatus::Normal) {
            forwardTickNum = tickNum;
            lastTickStats = tickStatus;
            tickStatus = WorldTickStatus::Forward;
            broadcastMsg("forwarding start");
            L_DEBUG("begin forward %s tick", tickNum);
        } else {
            broadcastMsg("this command can't be run in slow or wrap mode");
        }
    }

    void slowTick(size_t slowSpeed) {
        if (tickStatus == WorldTickStatus::Normal) {
            broadcastMsg("world has slowed %d times\n", slowSpeed);
            L_DEBUG("slow world %d times", slowSpeed);
            tickStatus = WorldTickStatus::Slow;
            SlowDownTimes = slowSpeed;
        } else {
            broadcastMsg("this command must be run at normal status\n");
        }
    }

    void profileWorld(Actor *player) {
        if (isProfiling) {
            waring(player, "another profiling is running");
            return;
        }
        if (tickStatus != WorldTickStatus::Normal) {
            waring(player, "you are not in normal mode,the result may be wrong");
        }
        L_DEBUG("begin profiling");
        info(player, "start profiling...");
        isProfiling = true;
        currentProfileRound = 50;
    }

    void sendProfileInfo() {
        L_DEBUG("end profiling");
        broadcastMsg(
                "mpst:            §2%.3f\n" \
               "    §r redstone:             §2%.3f\n" \
               "    §r chunk & village:      §2%.3f\n" \
               "    §r player:               §2%.3f\n" \
               "        §r chunk tick:           §2%.3f\n" \
               "            §r random tick & env:     §2%.3f\n" \
               "            §r blockEntities:   §2%.3f\n" \
               "            §r (de)spawn:       §2%.3f",
                (double) levelTickTime / 50000,
                (double) redstoneTickTime / 50000,
                (double) dimTickTime / 50000,
                (double) playerTickTime / 50000,
                (double) chunkTickTime / 50000,
                (double) randTickTime / 50000,
                (double) blockEntityTickTime / 50000,
                (double) spawnerTickTime / 50000
        );

    }

    void resetProfileCounter() {
        redstoneTickTime = 0;
        playerTickTime = 0;
        levelTickTime = 0;
        dimTickTime = 0;
        chunkTickTime = 0;
        randTickTime = 0;
        blockEntityTickTime = 0;
        spawnerTickTime = 0;
    }

    void mspt() {
        tick::isMSPTing = true;
    }
}


//所有情况下都执行
void lightExtraWork() {
    hopperCounterManager.tick();
}

//加速和快进的时候不会执行
void heavyExtraWork() {
    village::villageTask();
}

THook(
        void,
        MSSYM_B1QA4tickB1AE11ServerLevelB2AAA7UEAAXXZ,
        Level * serverLevel
) {
    if (!globalLevel) {
        globalLevel = serverLevel;
        initCommand();
        initRightClickManager();
        //   LOGF(getLogFile(), "init server level");
    }


    switch (tick::tickStatus) {
        case tick::Frozen:
            return;
        case tick::Normal:

            if (tick::isProfiling || tick::isMSPTing) {
                TIMER_START
                original(serverLevel);
                lightExtraWork();
                heavyExtraWork();
                TIMER_END
                if (tick::isMSPTing) {
                    auto mspt = (double) timeReslut / 1000;
                    int tps = mspt <= 50 ? 20 : (int) (1.0 / mspt);
                    broadcastMsg("mspt: %.3lf ms,tps: %d", mspt, tps);
                    tick::isMSPTing = false;
                }
                if (tick::isProfiling) {
                    tick::levelTickTime += timeReslut;
                    tick::currentProfileRound--;
                    if (tick::currentProfileRound == 0) {
                        tick::isProfiling = false;
                        tick::sendProfileInfo();
                        tick::resetProfileCounter();
                    }
                }
            } else {
                original(serverLevel);
                lightExtraWork();
                heavyExtraWork();
            }
            break;
        case tick::Slow:
            if (tick::slowDownCounter % tick::SlowDownTimes == 0) {
                original(serverLevel);
                lightExtraWork();
                heavyExtraWork();
            }
            tick::slowDownCounter = (tick::slowDownCounter + 1) % tick::SlowDownTimes;
            break;
        case tick::Forward:
            for (int i = 0; i < tick::forwardTickNum; i++) {
                original(serverLevel);
                lightExtraWork();
            }
            broadcastMsg("forwarding end %d tick passed", tick::forwardTickNum);
            tick::forwardTickNum = 0;
            tick::tickStatus = tick::lastTickStats;
            break;
        case tick::Wrap:
            for (int i = 0; i < tick::wrapSpeed; ++i) {
                original(serverLevel);
                lightExtraWork();
            }
            break;
    }
}

//ServerPlayer::tickWorld
THook(
        void,
        MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z,
        Actor *p,
        void * tick
) {
    original(p, tick);
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
        BlockSource *blockSource,
        Tick * tick
) {
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


//LevelChunk::tickBlockEntities
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

//mob actor Spawner::tick
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
    if (tick::isProfiling) {
        TIMER_START
        original(dim);
        TIMER_END
        tick::redstoneTickTime += timeReslut;
    } else {
        original(dim);
    }

    // auto v1 = *((int *) globalDimension + 69);
    // auto v2 = *((int *) globalDimension + 68);
    // printf("69%d 68%d\n", v1, v2);
    // printf("69:%d 68:%d\n", v1, v2);
}



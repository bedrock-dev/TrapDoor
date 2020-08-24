#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_TICKHOOK_H
#define TRAPDOOR_TICKHOOK_H

#include "lib/pch.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "Tick.h"

namespace SymHook {

    //Level::tick function, the top tick function(except redstone update)
    THook(void,
          MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ,
          void *l) {
        if (!globalLevel) { globalLevel = l; }
        //normal task
        if (tickStatus == TickStatus::Normal) {
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
        } else if (tickStatus == TickStatus::Forward) {
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
            tickStatus = TickStatus::Frozen;
        } else if (tickStatus == TickStatus::Slow) {
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
        if (!globalPlayer)globalPlayer = p;
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
        if (tickStatus == TickStatus::Normal) {
            if (tick::isProfiling) {
                TIMER_START
                original(dim);
                TIMER_END
                tick::redstoneUpdateTime += timeReslut;
            } else {
                original(dim);
            }
        }

        if (tickStatus == TickStatus::Forward) {
            original(dim);
        } else if (tickStatus == TickStatus::Slow) {
            if (slowDownCounter % SlowTimes == 0) {
                original(dim);
            }
        }
    }

}

#endif //TRAPDOOR_TICKHOOK_H
#pragma clang diagnostic pop
//
// Created by xhy on 2020/10/29.
//

#include "GameTick.h"
#include "commands/Command.h"
#include "tools/Message.h"
#include "tools/DirtyLogger.h"
#include "entity/Actor.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "ActorProfiler.h"

namespace mod::tick {
    using trapdoor::broadcastMsg;
    using trapdoor::warning;
    using trapdoor::error;
    using trapdoor::info;
    namespace {
        WorldTickStatus tickStatus = WorldTickStatus::Normal;
        WorldTickStatus lastTickStats = WorldTickStatus::Normal;

        mod::SimpleProfiler gameProfiler;
        size_t wrapSpeed = 1;
        int SlowDownTimes = 1;  //slow down time
        int slowDownCounter = 0; //slow down counter
        int forwardTickNum = 0; //forward tick num
        bool isMSPTing = false;

        mod::ActorProfiler &getActorProfiler() {
            static mod::ActorProfiler actorProfiler;
            return actorProfiler;
        }

        /*
         * 这个函数也是每gt执行一次的，但是不经过 TrapdoorMod,因此用static 来表示
         */
        void staticWork() {
            //实体性能分析的更新
            if (mod::tick::getActorProfiler().inProfiling) {
                auto &actorProfiler = mod::tick::getActorProfiler();
                actorProfiler.currentRound--;
                if (actorProfiler.currentRound == 0) {
                    actorProfiler.print();
                    actorProfiler.reset();
                }
            }
        }
    }

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
            broadcastMsg("forwarding start, %d tick last", tickNum);
            L_DEBUG("begin forward %d tick", tickNum);
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


    void profileWorld(trapdoor::Actor *player) {
        if (gameProfiler.inProfiling) {
            trapdoor::warning(player, "another profiling is running");
            return;
        }

        if (tickStatus != WorldTickStatus::Normal) {
            trapdoor::warning(player, "you are not in normal mode,the result may be wrong");
        }
        L_DEBUG("begin profiling");
        info(player, "start profiling...");
        gameProfiler.inProfiling = true;
        gameProfiler.currentRound = gameProfiler.totalRound;
    }

    void mspt() {
        tick::isMSPTing = true;
    }

    WorldTickStatus getTickStatus() {
        return tickStatus;
    }

    void profileEntities(trapdoor::Actor *player) {
        if (getActorProfiler().inProfiling) {
            trapdoor::warning(player, "another profiling is in running");
            return;
        }

        if (tick::getTickStatus() != tick::WorldTickStatus::Normal) {
            trapdoor::warning(player, "you are not in normal mode,the result may be wrong");
        }
        L_DEBUG("begin profiling");
        info(player, "start entities profiling...");
        getActorProfiler().inProfiling = true;
        getActorProfiler().currentRound = getActorProfiler().totalRound;
    }
}

using namespace SymHook;

THook(
        void,
        MSSYM_B1QA4tickB1AE11ServerLevelB2AAA7UEAAXXZ,
        trapdoor::Level * serverLevel
) {


    if (!trapdoor::bdsMod) {
        L_ERROR("mod is nullptr");
    }
    if (!trapdoor::bdsMod->getLevel()) {
        trapdoor::bdsMod->setLevel(serverLevel);
        trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()->initialize();
    }

    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();

    switch (mod::tick::tickStatus) {
        case mod::tick::Frozen:
            return;
        case mod::tick::Normal:

            if (mod::tick::gameProfiler.inProfiling || mod::tick::isMSPTing) {
                TIMER_START
                original(serverLevel);
                modInstance->lightTick();
                modInstance->heavyTick();
                mod::tick::staticWork();
                TIMER_END
                if (mod::tick::isMSPTing) {
                    auto mspt = (double) timeReslut / 1000;
                    int tps = mspt <= 50 ? 20 : (int) (1000.0 / mspt);
                    trapdoor::broadcastMsg("mspt: %.3lf ms tps: %d", mspt, tps);
                    mod::tick::isMSPTing = false;
                }
                if (mod::tick::gameProfiler.inProfiling) {
                    mod::tick::gameProfiler.serverLevelTickTime += timeReslut;
                    mod::tick::gameProfiler.currentRound--;
                    if (mod::tick::gameProfiler.currentRound == 0) {
                        mod::tick::gameProfiler.inProfiling = false;
                        mod::tick::gameProfiler.print();
                        mod::tick::gameProfiler.reset();
                    }
                }
            } else {
                original(serverLevel);
                modInstance->lightTick();
                modInstance->heavyTick();
                mod::tick::staticWork();
            }
            break;


        case mod::tick::Slow:
            if (mod::tick::slowDownCounter % mod::tick::SlowDownTimes == 0) {
                original(serverLevel);
                modInstance->lightTick();
                modInstance->heavyTick();
            }
            mod::tick::slowDownCounter = (mod::tick::slowDownCounter + 1) % mod::tick::SlowDownTimes;
            break;
        case mod::tick::Forward:
            for (auto i = 0; i < mod::tick::forwardTickNum; i++) {
                original(serverLevel);
                modInstance->lightTick();
            }
            trapdoor::broadcastMsg("forwarding end\n%d tick passed", mod::tick::forwardTickNum);
            mod::tick::forwardTickNum = 0;
            mod::tick::tickStatus = mod::tick::lastTickStats;
            break;
        case mod::tick::Wrap:
            for (int i = 0; i < mod::tick::wrapSpeed; ++i) {
                original(serverLevel);
                modInstance->lightTick();
            }
            modInstance->heavyTick();
            break;
    }
}

//ServerPlayer::tickWorld
THook(
        void,
        MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z,
        trapdoor::Actor *p,
        void * tick
) {
    original(p, tick);
}

//Dimension::tick
THook(
        void,
        MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ,
        void * dim
) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(dim);
        TIMER_END
        mod::tick::gameProfiler.dimensionTickTime += timeReslut;
    } else {
        original(dim);
    }
}
//LevelChunk::tick
THook(
        void,
        MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z,
        void *levelChunk,
        trapdoor::BlockSource *blockSource,
        Tick * tick
) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(levelChunk, blockSource, tick);
        TIMER_END
        mod::tick::gameProfiler.chunkTickTime += timeReslut;
        mod::tick::gameProfiler.tickChunkNum++;
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

    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(levelChunk, blockSource, a3, a4);
        TIMER_END
        mod::tick::gameProfiler.chunkRandomTickTime += timeReslut;
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
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(levelChunk, blockSource);
        TIMER_END
        mod::tick::gameProfiler.chunkBlockEntityTickTime += timeReslut;
    } else {
        original(levelChunk, blockSource);
    }
}

////mob actor Spawner::tick
//THook(
//        void,
//        MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEBVLevelChunkB3AAAA1Z,
//        void *swr,
//        void *blockSource,
//        void * chunk
//) {
////    if (!globalSpawner)globalSpawner = swr;
//    if (!swr) {
//        printf("spawner.tick --> spawner is nullptr");
//        return;
//    }
//    original(swr, blockSource, chunk);
////    if (mod::tick::isProfiling) {
////        TIMER_START
////        original(swr, blockSource, chunk);
////        TIMER_END
////        mod::tick::spawnerTickTime += timeReslut;
////    } else {
////    }
//
//}

//BlockTickingQueue::pendingTicks
//the server will crash if hook this function
THook(
        void,
        MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z,
        void *queue,
        trapdoor::BlockSource *source,
        const int *until,
        int max,
        bool instalTick
) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(queue, source, until, max, instalTick);
        TIMER_END
        mod::tick::gameProfiler.chunkPendingTickTime += timeReslut;
    } else {
        original(queue, source, until, max, instalTick);
    }
}

//Dimension::tick
THook(
        void,
        MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ,
        void * dim
) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(dim);
        TIMER_END
        mod::tick::gameProfiler.redstoneTickTime += timeReslut;
    } else {
        original(dim);
    }
    // auto v1 = *((int *) globalDimension + 69);
    // auto v2 = *((int *) globalDimension + 68);
    // printf("69%d 68%d\n", v1, v2);
    // printf("69:%d 68:%d\n", v1, v2);
}


THook(
        void,
        MSSYM_B1QA4tickB1AE13EntitySystemsB2AAE23QEAAXAEAVEntityRegistryB3AAAA1Z,
        void *entitySystem,
        void * registry
) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(entitySystem, registry);
        TIMER_END
        mod::tick::gameProfiler.levelEntitySystemTickTime += timeReslut;
    } else {
        original(entitySystem, registry);
    }
}



//实体性能分析的钩子函数
THook(
        void,
        MSSYM_B1QA4tickB1AA5ActorB2AAA4QEAAB1UE16NAEAVBlockSourceB3AAAA1Z,
        trapdoor::Actor *actor,
        trapdoor::BlockSource * blockSource
) {
    if (mod::tick::getActorProfiler().inProfiling) {
        auto &profiler = mod::tick::getActorProfiler();
        TIMER_START
        original(actor, blockSource);
        TIMER_END
        auto name = actor->getActorId();
        profiler.entitiesTickingList[name].time += timeReslut;
        profiler.entitiesTickingList[name].count++;
    } else {
        original(actor, blockSource);
    }
}
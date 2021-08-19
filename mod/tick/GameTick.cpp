//
// Created by xhy on 2020/10/29.
//

#include "GameTick.h"

#include "ActorProfiler.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "commands/Command.h"
#include "entity/Actor.h"
#include "lib/Remotery.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"

namespace mod::tick {
    using trapdoor::broadcastMsg;
    using trapdoor::error;
    using trapdoor::info;
    using trapdoor::warning;
    namespace {
        WorldTickStatus tickStatus = WorldTickStatus::Normal;
        WorldTickStatus lastTickStats = WorldTickStatus::Normal;

        mod::SimpleProfiler gameProfiler;
        size_t wrapSpeed = 1;
        int SlowDownTimes = 1;    // slow down time
        int slowDownCounter = 0;  // slow down counter
        int forwardTickNum = 0;   // forward tick num
        bool isMSPTing = false;

        mod::ActorProfiler &getActorProfiler() {
            static mod::ActorProfiler actorProfiler;
            return actorProfiler;
        }

        /*
         * 这个函数也是每gt执行一次的，但是不经过 TrapdoorMod,因此用static
         * 来表示
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

        void sendMsptInfo(microsecond_t time, bool isRedstoneTick) {
            auto mspt = (double)time / 1000;
            int tps = mspt <= 50 ? 20 : (int)(1000.0 / mspt);
            trapdoor::MessageBuilder builder;
            auto color = MSG_COLOR::WHITE;
            if (mspt > 40) {
                if (mspt >= 50) {
                    color = MSG_COLOR::RED;
                } else {
                    color = MSG_COLOR::YELLOW;
                }
            }
            auto rColor = isRedstoneTick ? MSG_COLOR::RED : MSG_COLOR::WHITE;
            builder.sText("#", rColor)
                .text("mspt: ")
                .sTextF(color, "%.3f ms ", mspt)
                .text("tps: ")
                .sTextF(color, "%d", tps)
                .broadcast();
        }
    }  // namespace

    void freezeTick() {
        if (tickStatus == WorldTickStatus::Normal) {
            // info("world has frozen");
            if (tickStatus != WorldTickStatus::Frozen) {
                tickStatus = WorldTickStatus::Frozen;
                L_DEBUG("freeze world");
                broadcastMsg(LANG("tick.fz.set"));
            }
        }
    }

    void resetTick() {
        if (tickStatus != WorldTickStatus::Normal) {
            tickStatus = WorldTickStatus::Normal;
            L_DEBUG("reset world");
        }
        broadcastMsg(LANG("tick.r.set"));
    }

    void wrapTick(size_t speed) {
        if (tickStatus == WorldTickStatus::Normal) {
            broadcastMsg(LANG("tick.acc.set"), speed);
            tickStatus = WorldTickStatus::Wrap;
            L_DEBUG("begin accelerate world %d", speed);
            wrapSpeed = speed;
        } else {
            broadcastMsg(LANG("tick.acc.error"));
        }
    }

    void forwardTick(size_t tickNum) {
        if (tickStatus == WorldTickStatus::Frozen ||
            tickStatus == WorldTickStatus::Normal) {
            forwardTickNum = tickNum;
            lastTickStats = tickStatus;
            tickStatus = WorldTickStatus::Forward;
            if (tickNum > 1200) broadcastMsg(LANG("tick.fw.begin"), tickNum);
            L_DEBUG("begin forward %d tick", tickNum);
        } else {
            broadcastMsg(LANG("tick.fw.error"));
        }
    }

    void slowTick(size_t slowSpeed) {
        if (tickStatus == WorldTickStatus::Normal) {
            broadcastMsg(LANG("tick.slow.set"), slowSpeed);
            L_DEBUG("slow world %d times", slowSpeed);
            tickStatus = WorldTickStatus::Slow;
            SlowDownTimes = slowSpeed;
        } else {
            broadcastMsg(LANG("tick.slow.error"));
        }
    }

    void profileWorld(trapdoor::Actor *player) {
        if (gameProfiler.inProfiling) {
            trapdoor::warning(player, LANG("prof.error"));
            return;
        }

        if (tickStatus != WorldTickStatus::Normal) {
            trapdoor::warning(player, LANG("prof.warning"));
        }
        L_DEBUG("begin profiling");
        broadcastMsg(LANG("prof.start"));
        gameProfiler.inProfiling = true;
        gameProfiler.currentRound = gameProfiler.totalRound;
    }

    void mspt() { tick::isMSPTing = true; }

    WorldTickStatus getTickStatus() { return tickStatus; }

    void profileEntities(trapdoor::Actor *player) {
        if (getActorProfiler().inProfiling) {
            trapdoor::warning(player, LANG("prof.error"));
            return;
        }

        if (tick::getTickStatus() != tick::WorldTickStatus::Normal) {
            trapdoor::warning(player, LANG("prof.warning"));
        }
        L_DEBUG("begin profiling");
        info(player, LANG("prof.start"));
        getActorProfiler().inProfiling = true;
        getActorProfiler().currentRound = getActorProfiler().totalRound;
    }

    void queryStatus(trapdoor::Actor *player) {
        switch (tickStatus) {
            case Frozen:
                info(player, "frozen");
                return;
            case Normal:
                info(player, "normal");
                return;
            case Slow:
                info(player, "slow %d times", tick::SlowDownTimes);
                return;
            case Forward:
                info(player, "forwarding");
                return;
            case Wrap:
                info(player, "accelerate %d times", tick::wrapSpeed);
                return;
        }
    }

    void registerTickCommand(CommandManager &commandManager) {
        commandManager.registerCmd("tick", "command.tick.desc")
            ->then(ARG("fz", "command.tick.fw.desc", NONE,
                       { tick::freezeTick(); }))
            ->then(ARG("slow", "command.tick.slow.desc", INT,
                       {
                           auto slowTime = holder->getInt();
                           if (slowTime > 1 && slowTime <= 64) {
                               tick::slowTick(slowTime);
                           } else {
                               error(player, LANG("command.tick.slow.error"));
                           }
                       }))
            ->then(ARG("acc", "command.tick.acc.desc", INT,
                       {
                           auto wrapTime = holder->getInt();
                           if (wrapTime > 1 && wrapTime <= 10) {
                               tick::wrapTick(wrapTime);
                           } else {
                               error(player, LANG("command.tick.acc.error"));
                           }
                       }))
            ->then(
                ARG("r", "command.tick.r.desc", NONE, { tick::resetTick(); }))
            ->then(ARG("fw", "command.tick.fw.desc", INT,
                       { tick::forwardTick(holder->getInt()); }))
            ->then(ARG("q", "command.tick.q.desc", NONE,
                       { tick::queryStatus(player); }));
    }

    void registerProfileCommand(CommandManager &commandManager) {
        commandManager.registerCmd("prof", "command.prof.desc")
            ->then(ARG("actor", "command.prof.actor.desc", NONE,
                       { tick::profileEntities(player); }))
            ->EXE({ tick::profileWorld(player); });
        commandManager.registerCmd("mspt", "command.mspt.desc")->EXE({
            tick::mspt();
        });
    }
}  // namespace mod::tick

using namespace SymHook;

THook(void, ServerLevel_tick_86efb826, trapdoor::Level *serverLevel) {
    if (!trapdoor::bdsMod) {
        L_ERROR("mod is nullptr");
    }
    if (!trapdoor::bdsMod->getLevel()) {
        L_DEBUG("init levle obj");
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
                    //发送mspt信息
                    bool isRedstoneTick = modInstance->getLevel()
                                              ->getDimFromID(0)
                                              ->isRedstoneTick();
                    mod::tick::sendMsptInfo(timeReslut, isRedstoneTick);
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
            mod::tick::slowDownCounter =
                (mod::tick::slowDownCounter + 1) % mod::tick::SlowDownTimes;
            break;
        case mod::tick::Forward:
            for (auto i = 0; i < mod::tick::forwardTickNum; i++) {
                original(serverLevel);
                modInstance->lightTick();
            }
            trapdoor::broadcastMsg(trapdoor::LANG("tick.fw.end"),
                                   mod::tick::forwardTickNum);
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

// ServerPlayer::tickWorld
// THook(void, SymHook::Serv, trapdoor::Actor *p, void *tick) {
//    original(p, tick);
//}

// Dimension::tick
THook(void, Dimension_tick_39d89862, void *dim) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(dim);
        TIMER_END
        mod::tick::gameProfiler.dimensionTickTime += timeReslut;
    } else {
        original(dim);
    }
}
// LevelChunk::tick
THook(void, LevelChunk_tick_9d729ccd, void *levelChunk,
      trapdoor::BlockSource *blockSource, size_t *tick) {
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

// LevelChunk::tickBlocks
THook(void, LevelChunk_tickBlocks_66280c26, void *levelChunk, void *blockSource,
      INT64 a3, int a4) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(levelChunk, blockSource, a3, a4);
        TIMER_END
        mod::tick::gameProfiler.chunkRandomTickTime += timeReslut;
    } else {
        original(levelChunk, blockSource, a3, a4);
    }
}

// LevelChunk::tickBlockEntities
THook(void, LevelChunk_tickBlockEntities_41f9b2ca, void *levelChunk,
      void *blockSource) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(levelChunk, blockSource);
        TIMER_END
        mod::tick::gameProfiler.chunkBlockEntityTickTime += timeReslut;
    } else {
        original(levelChunk, blockSource);
    }
}

// BlockTickingQueue::pendingTicks
THook(void, BlockTickingQueue_tickPendingTicks_e4625213, void *queue,
      trapdoor::BlockSource *source, const int *until, int max,
      bool instalTick) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(queue, source, until, max, instalTick);
        TIMER_END
        mod::tick::gameProfiler.chunkPendingTickTime += timeReslut;
    } else {
        original(queue, source, until, max, instalTick);
    }
}

// Dimension::tickRedstone
THook(void, Dimension_tickRedstone_c8a7e6e5, void *dim) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(dim);
        TIMER_END
        mod::tick::gameProfiler.redstoneTickTime += timeReslut;
    } else {
        original(dim);
    }

    // printf("69%d 68%d\n", v1, v2);
    // printf("69:%d 68:%d\n", v1, v2);
}

THook(void, Level_tickEntitySystems_251e10ba, void *level) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(level);
        TIMER_END
        mod::tick::gameProfiler.levelEntitySystemTickTime += timeReslut;
    } else {
        original(level);
    }
}

// pending update
//这个符号没了，直接测不准就不要这一条了
// THook(
//        void,
//
// MSSYM_B1QE21processPendingUpdatesB1AE17CircuitSceneGraphB2AAE20AEAAXPEAVBlockSourceB3AAAA1Z,
//        void *graph,
//        void * bs
//) {
//    if (mod::tick::gameProfiler.inProfiling) {
//        TIMER_START
//        original(graph, bs);
//        TIMER_END
//        mod::tick::gameProfiler.redstonePendingUpdateTime += timeReslut;
//    } else {
//        original(graph, bs);
//    }
//}

// pendingAdd
THook(void, CircuitSceneGraph_processPendingAdds_9d2954e5, void *graph) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(graph);
        TIMER_END
        mod::tick::gameProfiler.redstonePendingAddTime += timeReslut;
    } else {
        original(graph);
    }
}

// pnding remove
THook(void, CircuitSceneGraph_removeComponent_1f06081d, void *graph, void *bs) {
    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        original(graph, bs);
        TIMER_END
        mod::tick::gameProfiler.redstonePendingRemoveTime += timeReslut;
    } else {
        original(graph, bs);
    }
}

//实体性能分析的钩子函数
THook(void, Actor_tick_8589defc, trapdoor::Actor *actor,
      trapdoor::BlockSource *blockSource) {
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

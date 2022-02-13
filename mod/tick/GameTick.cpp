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
#include "lib/SymHook.h"
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
        size_t accSpeed = 1;
        int SlowDownTimes = 1;      // slow down time
        int slowDownCounter = 0;    // slow down counter
        size_t forwardTickNum = 0;  // forward tick num
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
            tickStatus = WorldTickStatus::Frozen;
            L_DEBUG("freeze world");
            broadcastMsg(LANG("tick.fz.set"));
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
            accSpeed = speed;
        } else {
            broadcastMsg(LANG("tick.acc.error"));
        }
    }

    void forwardTick(size_t tickNum) {
        if (tickStatus == WorldTickStatus::Frozen ||
            tickStatus == WorldTickStatus::Normal) {
            forwardTickNum = tickNum;
            //记录上次的状态以便恢复
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

    void profileWorld(trapdoor::Actor *player, int round, ProfileType t) {
        if (gameProfiler.inProfiling) {
            trapdoor::warning(player, LANG("prof.error"));
            return;
        }
        if (round <= 0 || round > 12000) {
            trapdoor::error(player, LANG("prof.c.error"));
            return;
        }
        if (tickStatus != WorldTickStatus::Normal) {
            trapdoor::warning(player, LANG("prof.warning"));
        }
        L_DEBUG("begin profiling");
        broadcastMsg(LANG("prof.start"));
        gameProfiler.profileType = t;
        gameProfiler.inProfiling = true;
        gameProfiler.totalRound = round;
        gameProfiler.currentRound = gameProfiler.totalRound;
    }

    void mspt() {
        if (!tick::isMSPTing) tick::isMSPTing = true;
    }

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
                info(player, "accelerate %d times", tick::accSpeed);
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
        commandManager
            .registerCmd("prof", "command.prof.desc")
            //自定义时常的基本测量
            ->then(ARG("c", "command.prof.c.desc", INT,
                       {
                           tick::profileWorld(player, holder->getInt(),
                                              ProfileType::Normal);
                       }))
            //实体分析
            ->then(ARG("actor", "command.prof.actor.desc", NONE,
                       { tick::profileEntities(player); }))
            //区块卡顿分析
            ->then(ARG("chunk", "command.prof.chunk.desc", NONE,
                       { tick::profileWorld(player, 10, ProfileType::Chunk); }))
            //计划可读长度分析
            ->then(ARG(
                "pt", "command.prof.pt.desc", NONE,
                { tick::profileWorld(player, 10, ProfileType::PendingTick); }))
            //默认基本分析(100gt)
            ->EXE({ tick::profileWorld(player, 100, ProfileType::Normal); });
        commandManager.registerCmd("mspt", "command.mspt.desc")->EXE({
            tick::mspt();
        });
    }
}  // namespace mod::tick

using namespace SymHook;
// Hook整个ServerLevel::tick函数来实现变速和暂停的功能
THook(void, ServerLevel_tick_86efb826, trapdoor::Level *serverLevel) {
    if (!trapdoor::bdsMod) {
        L_ERROR("mod is nullptr");
    }
    if (!trapdoor::bdsMod->getLevel()) {
        L_DEBUG("init level obj");
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
                    bool isRedstoneTick = false;
                    //发送mspt信息
                    //                    bool isRedstoneTick =
                    //                    modInstance->getLevel()
                    // ->getDimFromID(0)
                    // ->isRedstoneTick(); bool isRedstoneTick = false;
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
                //下次记得检查这里
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
            //换回上次的状态
            mod::tick::tickStatus = mod::tick::lastTickStats;
            break;
        case mod::tick::Wrap:
            for (int i = 0; i < mod::tick::accSpeed; ++i) {
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
THook(void, LevelChunk_tick_9d729ccd, trapdoor::LevelChunk *levelChunk,
      trapdoor::BlockSource *blockSource, size_t *tick) {
    if (mod::tick::gameProfiler.inProfiling) {
        auto p = levelChunk->getPosition();
        TIMER_START
        original(levelChunk, blockSource, tick);
        TIMER_END
        mod::tick::gameProfiler.chunkStat.counter[p] += timeReslut;
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
        mod::tick::gameProfiler.chunkStat.randomTick += timeReslut;
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
        mod::tick::gameProfiler.chunkStat.blockEntities += timeReslut;
    } else {
        original(levelChunk, blockSource);
    }
}

// BlockTickingQueue::pendingTicks
THook(void, BlockTickingQueue_tickPendingTicks_e4625213,
      trapdoor::BlockTickingQueue *queue, trapdoor::BlockSource *source,
      uint64_t until, int max, bool instalTick) {
    //上限调整为无限
    //  max = INT32_MAX;
    // if (queue->next.queue.size() != 0 && flag) {
    //     // printf("Tick = %llu queue size is (%zd,%zu)\n",
    //     queue->currentTick,
    //     //        queue->next.queue.size(), queue->active.queue.size());
    //     for (auto &i : queue->next.queue) {
    //         auto *b = i.data.block;
    //         printf("[%d %d %d >%s]", i.data.pos.x, i.data.pos.y,
    //         i.data.pos.z,
    //                b->getName().c_str());
    //     }
    //     printf("\n");
    // }

    if (mod::tick::gameProfiler.inProfiling) {
        TIMER_START
        if (!queue->next.queue.empty()) {
            auto tickData = queue->next.queue[0].data;
            mod::tick::gameProfiler.ptCounter[tickData.pos.toChunkPos()] =
                queue->next.queue.size();
        }
        original(queue, source, until, max, instalTick);
        TIMER_END
        mod::tick::gameProfiler.chunkStat.pendingTick += timeReslut;
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
        // mod::tick::gameProfiler.redstoneTickTime += timeReslut;
        mod::tick::gameProfiler.redstonStat.signals += timeReslut;
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
        mod::tick::gameProfiler.redstonStat.pendingAdd += timeReslut;

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
        mod::tick::gameProfiler.redstonStat.pendingRemove += timeReslut;
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

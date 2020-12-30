//
// Created by xhy on 2020/12/30.
//

#include "ActorProfiler.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "GameTick.h"
#include "tools/DirtyLogger.h"

namespace mod {

    namespace {

        ActorProfiler &getActorProfiler() {
            static ActorProfiler actorProfiler;
            return actorProfiler;
        }
    }

    void profileEntities(trapdoor::Actor *player) {
        if (getActorProfiler().inProfiling) {
            trapdoor::warning(player, "another profiling is running");
            return;
        }

        if (tick::getTickStatus() != tick::WorldTickStatus::Normal) {
            trapdoor::warning(player, "you are not in normal mode,the result may be wrong");
        }
        L_DEBUG("begin profiling");
        info(player, "start profiling...");
        getActorProfiler().inProfiling = true;
        getActorProfiler().currentRound = getActorProfiler().totalRound;
    }

    void ActorProfiler::print() const {
        trapdoor::MessageBuilder builder;
        microsecond_t totalTime = 0;
        auto rounds = static_cast<float >(this->totalRound * 1000);
        for (const auto &item:this->entitiesTickingList) {
            totalTime += item.second;
        }
        builder.textF("-- Entities profiler %.3fms --\n", totalTime / rounds);
        for (const auto &item:this->entitiesTickingList) {
            builder.textF("%s:     %.3fms\n", item.first.c_str(), item.second / rounds);
        }
        builder.broadcast();
    }

    void ActorProfiler::reset() {
        this->inProfiling = false;
        this->entitiesTickingList.clear();
        this->currentRound = 0;
    }
};








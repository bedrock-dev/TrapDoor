//
// Created by xhy on 2020/12/30.
//

#include "ActorProfiler.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "GameTick.h"
#include "tools/DirtyLogger.h"
#include <algorithm>

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
        size_t entityNum = 0;
        auto rounds = static_cast<float >(this->totalRound * 1000);
        //统计总量
        for (const auto &item:this->entitiesTickingList) {
            totalTime += item.second.time;
            entityNum += item.second.count;
        }
        builder.sTextF(trapdoor::MessageBuilder::BOLD | trapdoor::MessageBuilder::AQUA,

                       "\n- %.3fms(%d) --\n", totalTime / rounds, entityNum / this->totalRound);
        //排序
        std::vector<std::pair<std::string, ActorProfilerInfo>> info(entitiesTickingList.begin(),
                                                                    entitiesTickingList.end());
        //输出前num个
        std::sort(info.begin(), info.end(), [](const std::pair<std::string, ActorProfilerInfo> &i1,
                                               const std::pair<std::string, ActorProfilerInfo> &i2
        ) {
            return i1.second.time > i2.second.time;
        });
        for (auto &item : info) {
            builder.textF(" - %s       ", item.first.c_str())
                    .sTextF(trapdoor::MessageBuilder::GREEN, "%.3fms/(%d)\n",
                            item.second.time / rounds, item.second.count / this->totalRound);
        }
        builder.broadcast();
    }

    void ActorProfiler::reset() {
        this->inProfiling = false;
        this->entitiesTickingList.clear();
        this->currentRound = 0;
    }
};








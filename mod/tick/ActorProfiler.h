//
// Created by xhy on 2020/12/30.
//

#ifndef MOD_ACTORPROFILER_H
#define MOD_ACTORPROFILER_H

#include "entity/Actor.h"
#include "SimpleProfiler.h"
#include <set>
#include <map>

namespace mod {
    class ActorProfiler : noncopyable {
    public:
        struct ActorProfilerInfo {
            microsecond_t time = 0;
            size_t count = 0;
        };
        bool inProfiling = false;
        size_t totalRound = 100;
        size_t currentRound = 0;
        std::map<std::string, ActorProfilerInfo> entitiesTickingList;

        void print() const;

        void reset();
    };

}


#endif //MOD_ACTORPROFILER_H

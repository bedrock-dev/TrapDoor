//
// Created by xhy on 2020/12/30.
//

#ifndef MOD_SIMPLEPROFILER_H
#define MOD_SIMPLEPROFILER_H

#include <chrono>
#include <map>

#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "tools/noncopyable .h"

typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END                                                      \
    auto elapsed = timer_clock::now() - start;                         \
    long long timeReslut =                                             \
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed) \
            .count();

namespace mod {
    typedef long long microsecond_t;
    enum ProfileType { Normal, Chunk, PendingTick };

    //区块统计数据
    struct ChunkStat {
        std::map<trapdoor::BlockPos2, microsecond_t> counter;
        microsecond_t blockEntities = 0;
        microsecond_t randomTick = 0;
        microsecond_t pendingTick = 0;
        size_t tickTime = 0;
        inline void reset() {
            counter.clear();
            blockEntities = 0;
            randomTick = 0;
            pendingTick = 0;
            tickTime = 0;
        }
    };
    //红石统计数据
    struct RedstoneStat {
        microsecond_t signals = 0;
        microsecond_t pendingAdd = 0;
        microsecond_t pendingRemove = 0;
        microsecond_t pendingUpdate = 0;
        inline void reset() {
            signals = 0;
            pendingAdd = 0;
            pendingRemove = 0;
            pendingUpdate = 0;
        }

        microsecond_t total() const {
            return signals + pendingAdd + pendingRemove + pendingUpdate;
        }
    };

    class SimpleProfiler : noncopyable {
       public:
        ProfileType profileType;

        ChunkStat chunkStat;
        RedstoneStat redstonStat;
        microsecond_t serverLevelTickTime = 0;  // mspt
        microsecond_t dimensionTickTime = 0;    //区块加载卸载&村庄
        microsecond_t levelEntitySystemTickTime = 0;
        std::map<trapdoor::BlockPos2, size_t> ptCounter;
        size_t totalRound = 100;
        size_t currentRound = 0;
        bool inProfiling = false;
        //重重所有数据
        void reset() {
            serverLevelTickTime = 0;  // mspt
            dimensionTickTime = 0;    //区块加载卸载&村庄
            chunkStat.reset();
            levelEntitySystemTickTime = 0;  //实体系统更新
            redstonStat.reset();
            currentRound = 0;
            this->ptCounter.clear();
        }

        void print() const;

        void printChunks() const;

        void printPendingTicks() const;

        void printBasics() const;
    };

}  // namespace mod

#endif  // MOD_SIMPLEPROFILER_H

//
// Created by xhy on 2020/12/30.
//

#ifndef MOD_SIMPLEPROFILER_H
#define MOD_SIMPLEPROFILER_H

#include <chrono>
#include "entity/Actor.h"
#include "tools/noncopyable .h"

typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END auto elapsed = timer_clock::now() - start; long long timeReslut =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

namespace mod {
    typedef long long microsecond_t;

    class SimpleProfiler : noncopyable {
    public:
        microsecond_t serverLevelTickTime = 0; //mspt
        microsecond_t redstoneTickTime = 0; //红石更新
        microsecond_t dimensionTickTime = 0; //区块加载卸载&村庄
        microsecond_t chunkTickTime = 0; //区块更新
        microsecond_t chunkBlockEntityTickTime = 0; //方块实体更新
        microsecond_t chunkRandomTickTime = 0; //随机刻更新
        microsecond_t chunkPendingTickTime = 0; //计划刻更新
        microsecond_t chunkRandomPendingTickTime = 0; //随机计划刻更新
        microsecond_t levelEntitySystemTickTime = 0;
        microsecond_t redstonePendingUpdateTime = 0;
        microsecond_t redstonePendingAddTime = 0;
        microsecond_t redstonePendingRemoveTime = 0;
        microsecond_t trapdoorModTickTime = 0;
        size_t tickChunkNum = 0;
        size_t totalRound = 100;
        size_t currentRound = 0;
        bool inProfiling = false;

        void reset() {
            serverLevelTickTime = 0; //mspt
            redstoneTickTime = 0; //红石更新
            dimensionTickTime = 0; //区块加载卸载&村庄
            chunkTickTime = 0; //区块更新
            chunkBlockEntityTickTime = 0; //方块实体更新
            chunkRandomTickTime = 0; //随机刻更新
            chunkPendingTickTime = 0; //计划刻更新
            chunkRandomPendingTickTime = 0; //随机计划刻更新
            levelEntitySystemTickTime = 0; //实体系统更新
            redstonePendingAddTime = 0;
            redstonePendingRemoveTime = 0;
            redstonePendingUpdateTime = 0;
            trapdoorModTickTime = 0; //模组自身的更新时间(heavy tick)
            tickChunkNum = 0;
            currentRound = 0;
        }

        void print() const;
    };


}

#endif //MOD_SIMPLEPROFILER_H

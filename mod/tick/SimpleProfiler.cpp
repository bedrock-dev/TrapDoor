//
// Created by xhy on 2020/12/30.
//

#include "SimpleProfiler.h"
#include "tools/MsgBuilder.h"
#include "Message.h"
#include "entity/Actor.h"

namespace mod {
    //  serverLevelTickTime = 0; //mspt
    //            levelEntityTickTime = 0; //实体更新 O
    //            redstoneTickTime = 0; //红石更新O
    //            dimensionTickTime = 0; //区块加载卸载&村庄 O
    //            chunkTickTime = 0; //区块更新 O
    //            chunkBlockEntityTickTime = 0; //方块实体更新
    //            chunkRandomTickTime = 0; //随机刻更新
    //            chunkPendingTickTime = 0; //计划刻更新
    //            chunkRandomPendingTickTime = 0; //随机计划刻更新
    //            levelEntitySystemTickTime = 0; //实体系统更新 O
    void SimpleProfiler::print() const {
        auto rounds = static_cast<float >(this->totalRound * 1000);
        int tps = static_cast<int>( 1000.0 / (serverLevelTickTime / rounds));
        if (tps > 20) tps = 20;
        trapdoor::MessageBuilder builder;
        builder.textF("Total mspt:    %.3fms   TPS:  %d\n", serverLevelTickTime / rounds, tps)
                .textF("Redstone:    %.3fms\n", redstoneTickTime / rounds)
                .textF("entitySystem:    %.3fms\n", levelEntitySystemTickTime / rounds)
                .textF("Chunk (un)load and village:    %.3fms\n", dimensionTickTime / rounds)
                .textF("total %zu chunks in ticking:    %.3fms\n", tickChunkNum / totalRound,
                       chunkTickTime / rounds)
                .textF("    block entity:    %.3fms\n", chunkBlockEntityTickTime / rounds)
                .textF("    random tick:    %.3fms\n", chunkRandomTickTime / rounds)
                .textF("     pending tick:     %.3f/%.3fms\n", chunkRandomPendingTickTime / rounds,
                       chunkPendingTickTime / rounds)
                .broadcast();
    }
}



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
        auto totalRedstoneTickTime =
                static_cast<float>
                (redstoneTickTime + redstonePendingUpdateTime + redstonePendingRemoveTime) /
                rounds;
        builder.textF("Total mspt:    %.3fms   TPS:  %d\n", serverLevelTickTime / rounds, tps)
                .textF(" - Redstone:    %.3fms\n", totalRedstoneTickTime)
                .textF("   - SignalUpdate:    %.3fms\n", redstoneTickTime / rounds)
                .textF("   - PendingUpdate:    %.3fms\n", redstonePendingUpdateTime / rounds)
                .textF("   - PendingAdd:    %.3fms\n", redstonePendingAddTime / rounds)
                .textF("   - PendingRemove:    %.3fms\n", redstonePendingRemoveTime / rounds)
                .textF(" - EntitySystem:    %.3fms\n", levelEntitySystemTickTime / rounds)
                .textF(" - Chunk (un)load & village:    %.3fms\n", dimensionTickTime / rounds)
                        // .textF("Trapdoor: %.3fms", trapdoorModTickTime / rounds)
                .textF(" - Chunk tick:    %.3fms (%d)\n", chunkTickTime / rounds, tickChunkNum / totalRound)
                .textF("   - Block entity:    %.3fms\n", chunkBlockEntityTickTime / rounds)
                .textF("   - Random tick:    %.3fms\n", chunkRandomTickTime / rounds)
                .textF("   - Pending tick:    %.3f/%.3fms\n", chunkRandomPendingTickTime / rounds,
                       chunkPendingTickTime / rounds)
                .broadcast();
    }
}


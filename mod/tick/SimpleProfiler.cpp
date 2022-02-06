//
// Created by xhy on 2020/12/30.
//

#include "SimpleProfiler.h"

#include "DirtyLogger.h"
#include "Message.h"
#include "entity/Actor.h"
#include "tools/MsgBuilder.h"

namespace mod {

    namespace {

        void addShowItem(trapdoor::MessageBuilder &builder,
                         const std::string &prefix, const std::string &key,
                         float value, float mspt) {
            builder.sText(prefix, trapdoor::MSG_COLOR::GRAY);
            auto color = trapdoor::MSG_COLOR::WHITE;
            if (mspt > 40 && mspt <= 50) {
                if (value / mspt > 0.25) {
                    color = trapdoor::MSG_COLOR::YELLOW;
                }
            } else if (mspt > 50) {
                auto ratio = value / mspt;
                if (ratio > 0.2 && ratio < 0.4) {
                    color = trapdoor::MSG_COLOR::YELLOW;
                } else if (ratio >= 0.4) {
                    color = trapdoor::MSG_COLOR::RED;
                }
            }
            builder.sTextF(color, key + ": ", trapdoor::MSG_COLOR::WHITE)
                .sTextF(color | trapdoor::MessageBuilder::BOLD, "%.3fms\n",
                        value);
        }
    }  // namespace

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
        auto rounds = static_cast<float>(this->totalRound * 1000);
        float mspt = serverLevelTickTime / rounds;
        int tps = static_cast<int>(1000.0 / mspt);
        if (tps > 20) tps = 20;
        trapdoor::MessageBuilder builder;
        auto totalRedstoneTickTime =
            static_cast<float>(redstoneTickTime + redstonePendingUpdateTime +
                               redstonePendingRemoveTime) /
            rounds;

        auto firstLineColor =
            trapdoor::MSG_COLOR::WHITE || trapdoor::MSG_COLOR::BOLD;
        builder.sTextF(firstLineColor, "MSPT:  ");

        auto color = trapdoor::MSG_COLOR::WHITE;
        if (mspt > 40 && mspt <= 50) {
            color = trapdoor::MSG_COLOR::YELLOW;
        } else if (mspt > 50) {
            color = trapdoor::MSG_COLOR::RED;
        }
        color |= trapdoor::MSG_COLOR::BOLD;

        builder.sTextF(color, "%.3fms", mspt)
            .sTextF(firstLineColor, "  TPS: ")
            .sTextF(color, "%d", tps)
            .sTextF(firstLineColor, "  CHUNKS: %d\n",
                    tickChunkNum / this->totalRound);
        addShowItem(builder, " - ", "Redstone", totalRedstoneTickTime, mspt);

        addShowItem(builder, "     - ", "SignalUpdate",
                    redstoneTickTime / rounds, mspt);
        builder.sText("  - ", trapdoor::MSG_COLOR::GRAY)
            .text("PendingUpdate: Invalid\n");
        addShowItem(builder, "     - ", "PendingRemove",
                    redstonePendingRemoveTime / rounds, mspt);

        addShowItem(builder, " - ", "EntitySystem",
                    levelEntitySystemTickTime / rounds, mspt);
        addShowItem(builder, " - ", "Chunk (un)load & village",
                    dimensionTickTime / rounds, mspt);

        addShowItem(builder, " - ", "ChunkTick", chunkTickTime / rounds, mspt);

        addShowItem(builder, "     - ", "BlockEntities",
                    chunkBlockEntityTickTime / rounds, mspt);
        addShowItem(builder, "     - ", "RandomTick",
                    chunkRandomTickTime / rounds, mspt);

        addShowItem(builder, "     - ", "PendingTick",
                    chunkPendingTickTime / rounds, mspt);
        builder.broadcast();

        //     .textF(" - Chunk tick:    %.3fms (%d)\n", chunkTickTime / rounds,
        //            tickChunkNum / totalRound)
        //         .textF("   - Block entity:    %.3fms\n",
        //                chunkBlockEntityTickTime / rounds)
        //     .textF("   - Random tick:    %.3fms\n", chunkRandomTickTime /
        //     rounds)
        //         .textF("   - Pending tick:    %.3f/%.3fms\n",
        //                chunkRandomPendingTickTime / rounds,
        //                chunkPendingTickTime / rounds)
        //         .text("   - Entity tick:    may be the rest")
        //         .broadcast();
    }
}  // namespace mod

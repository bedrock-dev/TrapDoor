//
// Created by xhy on 2020/12/30.
//

#include "SimpleProfiler.h"
#include "Message.h"
#include "entity/Actor.h"
#include "tools/MsgBuilder.h"

namespace mod {

namespace {

void addShowItem(trapdoor::MessageBuilder &builder, const std::string &prefix,
                 const std::string &key, float value) {

    builder.sText(prefix, trapdoor::MSG_COLOR::GRAY)
        .sText(key + ": ", trapdoor::MSG_COLOR::WHITE)
        .sTextF(trapdoor::MSG_COLOR::WHITE | trapdoor::MessageBuilder::BOLD,
                "%.3fms\n", value);
}
} // namespace

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
    int tps = static_cast<int>(1000.0 / (serverLevelTickTime / rounds));
    if (tps > 20)
        tps = 20;
    trapdoor::MessageBuilder builder;
    auto totalRedstoneTickTime =
        static_cast<float>(redstoneTickTime + redstonePendingUpdateTime +
                           redstonePendingRemoveTime) /
        rounds;

    builder.textF("MSPT:  ");
    auto color =
        tps < 20 ? trapdoor::MSG_COLOR::RED : trapdoor::MSG_COLOR::WHITE;
    builder.sTextF(color, "%.3fms", serverLevelTickTime / rounds)
        .text("  TPS: ")
        .sTextF(color, "%d", tps)
        .textF("  Chunks: %d\n", tickChunkNum / this->totalRound);
    addShowItem(builder, " - ", "Redstone", totalRedstoneTickTime);
    addShowItem(builder, "   - ", "SignalUpdate", redstoneTickTime / rounds);

    builder.sText("  - ", trapdoor::MSG_COLOR::GRAY)
        .text("PendingUpdate: Invalid\n");
    addShowItem(builder, "   - ", "PendingRemove",
                redstonePendingRemoveTime / rounds);

    addShowItem(builder, " - ", "EntitySystem",
                levelEntitySystemTickTime / rounds);
    addShowItem(builder, " - ", "Chunk (un)load & village",
                dimensionTickTime / rounds);

    addShowItem(builder, " - ", "ChunkTick", chunkTickTime / rounds);

    addShowItem(builder, "   - ", "BlockEntities",
                chunkBlockEntityTickTime / rounds);
    addShowItem(builder, "   - ", "RandomTick", chunkRandomTickTime / rounds);

    addShowItem(builder, "   - ", "PendingTick", chunkPendingTickTime / rounds);

    builder.broadcast();

    //     .textF(" - Chunk tick:    %.3fms (%d)\n", chunkTickTime / rounds,
    //            tickChunkNum / totalRound)
    //         .textF("   - Block entity:    %.3fms\n",
    //                chunkBlockEntityTickTime / rounds)
    //     .textF("   - Random tick:    %.3fms\n", chunkRandomTickTime / rounds)
    //         .textF("   - Pending tick:    %.3f/%.3fms\n",
    //                chunkRandomPendingTickTime / rounds,
    //                chunkPendingTickTime / rounds)
    //         .text("   - Entity tick:    may be the rest")
    //         .broadcast();
}
} // namespace mod

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
        if (this->profileType == ProfileType::Normal) {
            this->printBasics();
        } else if (this->profileType == ProfileType::Chunk) {
            this->printChunks();
        } else if (this->profileType == ProfileType::PendingTick) {
            this->printPendingTicks();
        }
    }

    void SimpleProfiler::printChunks() const {
        microsecond_t chunkTickTime = 0;
        auto rounds = static_cast<float>(this->totalRound * 1000);
        std::vector<std::pair<trapdoor::BlockPos2, microsecond_t>> data;
        for (auto &kv : this->chunkStat.counter) {
            data.push_back(kv);
            chunkTickTime += kv.second;
        }
        std::sort(data.begin(), data.end(),
                  [](const std::pair<trapdoor::BlockPos2, microsecond_t> &p1,
                     const std::pair<trapdoor::BlockPos2, microsecond_t> &p2) {
                      return p1.second > p2.second;
                  });
        int count = 10;
        if (count > data.size()) {
            count = data.size();
        }
        trapdoor::MessageBuilder builder;

        builder.textF("%zu chunks ticked, %.3f ms total\n",
                      this->chunkStat.counter.size(), chunkTickTime / rounds);
        for (int i = 0; i < count; i++) {
            auto &d = data[i];
            builder.sText(" - ", trapdoor::MSG_COLOR::GRAY);
            builder
                .sTextF(trapdoor::MSG_COLOR::WHITE, "[%d,%d]       ",
                        d.first.x * 16 + 8, d.first.z * 16 + 8)
                .sTextF(trapdoor::MSG_COLOR::GREEN, "%.3f", d.second / rounds)
                .text("ms\n");
        }

        builder.broadcast();
    }

    void SimpleProfiler::printPendingTicks() const {
        int totalPtLen = 0;

        std::vector<std::pair<trapdoor::BlockPos2, size_t>> data;
        for (auto &kv : this->ptCounter) {
            data.push_back(kv);
            totalPtLen += kv.second;
        }

        std::sort(data.begin(), data.end(),
                  [](const std::pair<trapdoor::BlockPos2, microsecond_t> &p1,
                     const std::pair<trapdoor::BlockPos2, microsecond_t> &p2) {
                      return p1.second > p2.second;
                  });
        int count = 10;
        if (count > data.size()) {
            count = data.size();
        }
        trapdoor::MessageBuilder builder;
        builder.textF(
            "%zu chunks ticked,here are the cached pending tick size\n",
            this->chunkStat.counter.size());
        for (int i = 0; i < count; i++) {
            auto &d = data[i];
            builder.sText(" - ", trapdoor::MSG_COLOR::GRAY);
            builder.sTextF(trapdoor::MSG_COLOR::WHITE, "[%d,%d]       ",
                           d.first.x * 16 + 8, d.first.z * 16 + 8);
            int num = d.second / this->totalRound;
            auto color = num >= 100 ? trapdoor::MSG_COLOR::RED
                                    : trapdoor::MSG_COLOR::GREEN;
            builder.sTextF(color, "%d\n", d.second / this->totalRound);
        }
        builder.broadcast();
    }

    void SimpleProfiler::printBasics() const {
        auto rounds = static_cast<float>(this->totalRound * 1000);
        float mspt = serverLevelTickTime / rounds;
        int tps = static_cast<int>(1000.0 / mspt);
        if (tps > 20) tps = 20;
        trapdoor::MessageBuilder builder;
        auto totalRedstoneTickTime =
            static_cast<float>(this->redstonStat.total()) / rounds;

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

        microsecond_t chunkTickTime = 0;
        for (auto &data : this->chunkStat.counter) {
            chunkTickTime += data.second;
        }

        builder.sTextF(color, "%.3fms", mspt)
            .sTextF(firstLineColor, "  TPS: ")
            .sTextF(color, "%d", tps)
            .sTextF(firstLineColor, "  CHUNKS: %d\n", chunkStat.counter.size());
        addShowItem(builder, " - ", "Redstone", totalRedstoneTickTime, mspt);
        addShowItem(builder, "     - ", "SignalUpdate",
                    redstonStat.signals / rounds, mspt);
        builder.sText("  - ", trapdoor::MSG_COLOR::GRAY)
            .text("PendingUpdate: Invalid\n");
        addShowItem(builder, "     - ", "PendingRemove",
                    redstonStat.pendingRemove / rounds, mspt);

        addShowItem(builder, " - ", "EntitySystem",
                    levelEntitySystemTickTime / rounds, mspt);
        addShowItem(builder, " - ", "Chunk (un)load & village",
                    dimensionTickTime / rounds, mspt);

        addShowItem(builder, " - ", "ChunkTick", chunkTickTime / rounds, mspt);
        addShowItem(builder, "     - ", "BlockEntities",
                    chunkStat.blockEntities / rounds, mspt);
        addShowItem(builder, "     - ", "RandomTick",
                    chunkStat.randomTick / rounds, mspt);
        addShowItem(builder, "     - ", "PendingTick",
                    chunkStat.pendingTick / rounds, mspt);
        builder.broadcast();
    }
}  // namespace mod

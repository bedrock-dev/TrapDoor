//
// Created by xhy on 2020/8/29.
//

#include "Player.h"
#include "lib/mod.h"
#include "block/Block.h"
#include "common/Common.h"
#include <queue>
#include "tools/MathTool.h"
#include "tools/MessageBuilder.h"
#include "level/Biome.h"

using namespace SymHook;

void showBiome(Actor *player, const BlockPos &pos, Block &block, int max) {
    Biome *biome = player->getBlockSource()->getBiome(&pos);
    std::string biomeName = biome->getBiomeName();
    printf("%s", biomeName.c_str());
    std::queue<BlockPos> placeQueue;
    placeQueue.push(pos);
    int num = 0;
    while (!placeQueue.empty() && num < max) {
        auto f = placeQueue.front();
        placeQueue.pop();
        std::vector<BlockPos> list = f.getPlainNeighbourPos();
        for (BlockPos position:list) {
            auto name = player->getBlockSource()->getBiome(&position)->getBiomeName();
            if (name == biomeName) {
                placeQueue.push(position);
            }
        }
        player->getBlockSource()->setBlock(&f, &block);
        num++;
    }
}

MeasureManager measureManager;
//player place block
THook(
        int64_t,
        MSSYM_B1QE21onBlockPlacedByPlayerB1AE34VanillaServerGameplayEventListenerB2AAA4UEAAB1QE14AW4EventResultB2AAE10AEAVPlayerB2AAA9AEBVBlockB2AAE12AEBVBlockPosB3AAUA1NB1AA1Z,
        void *self,
        Actor *player,
        Block &block,
        const BlockPos &pos,
        bool flag
) {
    auto name = block.getName();
  //  showBiome(player, pos, block, 16384);
//    if (name == "minecraft:warped_planks") {
//        measureManager.setPos1(pos);
//    } else if (name == "minecraft:crimson_planks") {
//        measureManager.setPos2(pos);
//    }
    return original(self, player, block, pos, flag);
}


//chain call





//player destroy block
THook(
        void,
        MSSYM_B2QUE20destroyBlockInternalB1AA8GameModeB2AAA4AEAAB1UE13NAEBVBlockPosB2AAA1EB1AA1Z,
        void *self,
        const BlockPos *pos,
        int64_t a3,
        int a4
) {
//    Block *block = globalBlockSource->getBlock(*pos);
//    auto blockName = block->getName();
    original(self, pos, a3, a4);
//    if (blockName != "minecraft:air") {
//        chainDestroy(pos, blockName, 20);
//    }
}


void MeasureManager::setPos1(const BlockPos pos) {
    if (!enableMarkPos)return;
    pos1 = pos;
    pos1Valid = true;
    if (pos1Valid && pos2Valid) {
        print();
    } else {
        sendSetInfo(1);
    }
}

void MeasureManager::setPos2(const BlockPos pos) {
    if (!enableMarkPos)return;
    pos2 = pos;
    pos2Valid = true;
    if (pos1Valid && pos2Valid) {
        print();
    } else {
        sendSetInfo(2);
    }
}


void MeasureManager::print() {
    auto d1 = math::distance(pos1.toVec3(), pos2.toVec3());
    auto d2 = math::distance(pos1.toVec3(), pos2.toVec3(), false, false);
    auto d3 = math::distance(pos1.toVec3(), pos2.toVec3(), true);
    auto d4 = math::distance(pos1.toVec3(), pos2.toVec3(), true, false);
    MessageBuilder builder;
    builder.text("from ")
            .pos(pos1)
            .text(" to ")
            .pos(pos2)
            .text(" :\nEuclidean: ")
            .num(d1)
            .text(" (")
            .num(d2)
            .text(") Manhattan: ")
            .num(d3)
            .text(" (")
            .num(d4)
            .text(")");
    //  .send();

}

void MeasureManager::sendSetInfo(int index) {
    auto p = index == 1 ? pos1 : pos2;
    MessageBuilder builder;
    builder.text("position ")
            .num(index)
            .text(" set to ")
            .pos(p);
    //  .send();
}

//
// Created by xhy on 2020/8/29.
//

#include "Player.h"
#include "lib/mod.h"
#include "lib/pch.h"
#include "block/Block.h"
#include "tools/dbg.h"
#include "common/Common.h"
#include "tools/Message.h"
#include <queue>
#include "entity/Actor.h"

using namespace SymHook;

MeasureManager measureManager;
int piston_aux = 0;
//player place block
THook(
        int64_t,
        MSSYM_B1QE21onBlockPlacedByPlayerB1AE34VanillaServerGameplayEventListenerB2AAA4UEAAB1QE14AW4EventResultB2AAE10AEAVPlayerB2AAA9AEBVBlockB2AAE12AEBVBlockPosB3AAUA1NB1AA1Z,
        void *self,
        void *player,
        Block &block,
        const BlockPos &pos,
        bool flag
) {
    auto name = block.getName();
    if (name == "minecraft:warped_planks") {
        measureManager.setPos1(pos);
    } else if (name == "minecraft:crimson_planks") {
        measureManager.setPos2(pos);
    }
    dbg(name);
    return original(self, player, block, pos, flag);

}


//player destroy block chained
void chainDestroy(const BlockPos *pos, const std::string &blockName, int max) {
    auto air = globalBlockSource->getBlock(*pos);
    std::queue<BlockPos> destroyQueue;
    destroyQueue.push(*pos);
    int num = 0;
    while (!destroyQueue.empty() && num < max) {
        auto f = destroyQueue.front();
        destroyQueue.pop();
        std::vector<BlockPos> list = f.getNeighbourPos();
        for (BlockPos position:list) {
            auto block = globalBlockSource->getBlock(position);
            if (block->getName() == blockName) {
                destroyQueue.push(position);
            }
        }
        globalBlockSource->setBlock(&f, air);
        num++;
    }
}





//player destroy block
THook(
        void,
        MSSYM_B2QUE20destroyBlockInternalB1AA8GameModeB2AAA4AEAAB1UE13NAEBVBlockPosB2AAA1EB1AA1Z,
        void *self,
        const BlockPos *pos,
        int64_t a3,
        int a4
) {
    Block *block = globalBlockSource->getBlock(*pos);
    auto blockName = block->getName();
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
            .text(")")
            .send();

}

void MeasureManager::sendSetInfo(int index) {
    auto p = index == 1 ? pos1 : pos2;
    MessageBuilder builder;
    builder.text("position ")
            .num(index)
            .text(" set to ")
            .pos(p)
            .send();
}

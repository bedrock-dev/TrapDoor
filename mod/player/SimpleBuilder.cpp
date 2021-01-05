//
// Created by xhy on 2021/1/5.
//

#include "SimpleBuilder.h"
#include "entity/Actor.h"
#include "block/BlockSource.h"
#include "block/Block.h"
#include "graphics/BlockPos.h"

namespace mod {
    void SimpleBuilder::buildCircle(trapdoor::Actor *player, size_t radius, bool hollow) const {
        if (!this->enable)return;
        trapdoor::BlockPos standPos = player->getStandPosition();
        auto block = player->getBlockSource()->getBlock(standPos.x, standPos.y, standPos.z);
        trapdoor::BlockPos pos = standPos;
        //在这里写画圆
        for (int i = 0; i < radius; i++) {
            for (int j = 0; j < radius; ++j) {
                pos.x = standPos.x + i;
                pos.z = standPos.z + j;
                player->getBlockSource()->setBlock(&pos, block);
            }
        }
    }

    void SimpleBuilder::buildSphere(trapdoor::Actor *player, size_t radius, bool hollow) const {
        if (!this->enable)return;
        trapdoor::BlockPos standPos = player->getStandPosition();
        auto block = player->getBlockSource()->getBlock(standPos.x, standPos.y, standPos.z);
        //在这里写

    }
}

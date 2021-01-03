//
// Created by xhy on 2021/1/3.
//

#include "BlockRotationHelper.h"
#include "block/Block.h"
#include "block/BlockSource.h"
#include "graphics/BlockPos.h"

namespace mod {
    void BlockRotationHelper::rotate(trapdoor::BlockPos &pos, trapdoor::BlockSource *blockSource) const {
        using trapdoor::BlockSource;
        if (!this->enable)return;
        auto block = blockSource->getBlock(pos);
        auto variant = block->getVariant();
        auto name = block->getName();
        //在这里根据不同的方块进行不同的旋转操作
        /**
         * if(name == "**slab")
         * this.rotatSlab(); //参数转发过去
         */

        //下面是一个改变状态的例子
//        auto newState = (variant + 1) % 16;
//        auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
//        blockSource->setBlock(&pos, newBlock);
    }

    void BlockRotationHelper::rotateSlabBlock() {

    }
}

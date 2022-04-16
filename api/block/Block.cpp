//
// Created by xhy on 2020/8/26.
//
#include "Block.h"

#include "Offset.h"
#include "tools/CastHelper.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"

namespace trapdoor {
    using namespace SymHook;

    //获取方块legacy
    BlockLegacy *Block::getLegacy() {
        return *offset_cast<BlockLegacy **>(this, off::BLOCK_GET_LEGACY);
    }

    //获取方块名字
    std::string Block::getName() {
        std::string debugStr;
        SYM_CALL(void (*)(void *block, std::string &),
                 Block_toDebugString_522cb860, this, debugStr);
        // return debugStr.erase(0, 6);
        return debugStr;
    }

    //获取特殊值
    int Block::getVariant() {
        return *offset_cast<char *>(this, off::BLOCK_GET_VARIANT);
    }

    //获取方块实体的位置
    BlockPos *BlockActor::getPosition() {
        return offset_cast<BlockPos *>(this, off::BLOCKACTOR_GET_POSITION);
        // return reinterpret_cast<BlockPos *>(reinterpret_cast<VA>(this) + 44);
    }
    BlockSource *BlockActor::getBlockSource() {
        // TODO
        return nullptr;
    }

}  // namespace trapdoor

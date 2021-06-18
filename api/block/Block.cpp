//
// Created by xhy on 2020/8/26.
//
#include <vector>
#include "Block.h"
#include "tools/Message.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "block/BlockLegacy.h"
#include "tools/DirtyLogger.h"
#include "tools/CastHelper.h"
#include "Offset.h"

namespace trapdoor {
    using namespace SymHook;

    //获取方块legacy
    BlockLegacy *Block::getLegacy() {
        return *offset_cast<BlockLegacy **>(this, off::BLOCK_GET_LEGACY);
    }


    //获取方块名字
    std::string Block::getName() {
        std::string debugStr;
        SYM_CALL(
                void(*)(void * block, std::string &),
            MSSYM_MD5_522cb860cf3cdc8b90657ccbea278782,
                this, debugStr);
        return debugStr.erase(0, 6);
    }

    //获取特殊值
    int Block::getVariant() {
        return *offset_cast<char *>(this, off::BLOCK_GET_VARIANT);
    }

    //获取方块实体的位置
    BlockPos *BlockActor::getPosition() {
        return offset_cast<BlockPos *>(this, off::BLOCKACTOR_GET_POSITION);
        //return reinterpret_cast<BlockPos *>(reinterpret_cast<VA>(this) + 44);
    }

}


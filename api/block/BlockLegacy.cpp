//
// Created by xhy on 2020/12/16.
//

#include "BlockLegacy.h"

#include "Offset.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/CastHelper.h"

namespace trapdoor {
    using namespace SymHook;

    //获取某个特殊值状态下的方块对象
    Block* BlockLegacy::tryGetStateBlock(unsigned short state) {
        return SYM_CALL(Block * (*)(BlockLegacy*, unsigned short),
                        BlockLegacy_tryGetStateFromLegacyData_ad225111, this,
                        state);
    }

    BlockType BlockLegacy::getBlockID() {
        return (BlockType)*offset_cast<short*>(this,
                                               off::BLOCKLEGACY_GET_BLOCK_ID);
    }
}  // namespace trapdoor

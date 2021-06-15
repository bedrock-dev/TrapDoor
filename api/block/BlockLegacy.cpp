//
// Created by xhy on 2020/12/16.
//
#include "lib/Loader.h"
#include <vector>
#include "BlockLegacy.h"
#include "tools/CastHelper.h"
#include "Offset.h"

namespace trapdoor {

    std::string BlockLegacy::getDebugText() {
        std::vector<std::string> vector;
        SymCall("?getDebugText@BlockLegacy@@QEBAXAEAV?$vector@V?$basic_string@DU?$char_t"
            "raits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_t"
            "raits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z",
            void, BlockLegacy*, std::vector<std::string> &)(this, vector);
        return vector.empty() ? "unknown" : vector[0];
    }

    //获取某个特殊值状态下的方块对象
    Block *BlockLegacy::tryGetStateBlock(unsigned short state) {
        return SymCall("?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z", Block*, BlockLegacy*, unsigned short)(this, state);
    }

    BlockType BlockLegacy::getBlockID() {
        return (BlockType) *offset_cast<short *>(this, off::BLOCKLEGACY_GET_BLOCK_ID);
    }
}



//
// Created by xhy on 2020/12/16.
//

#include "BlockLegacy.h"
#include "Offset.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/CastHelper.h"
#include <vector>

namespace trapdoor {
using namespace SymHook;

std::string BlockLegacy::getDebugText() {
    std::vector<std::string> vector;
    SYM_CALL(void (*)(BlockLegacy *, std::vector<std::string> &),
             MSSYM_MD5_794b421b4bf67101f7418cd0d78bad83, this, vector);
    //   return "this api was removed";
    return vector.empty() ? "unknown" : vector[0];
}

//获取某个特殊值状态下的方块对象
Block *BlockLegacy::tryGetStateBlock(unsigned short state) {
    return SYM_CALL(
        Block * (*)(BlockLegacy *, unsigned short),
        MSSYM_B1QE25tryGetStateFromLegacyDataB1AE11BlockLegacyB2AAE13QEBAPEBVBlockB2AAA1GB1AA1Z,
        this, state);
}

BlockType BlockLegacy::getBlockID() {
    return (BlockType)*offset_cast<short *>(this,
                                            off::BLOCKLEGACY_GET_BLOCK_ID);
}
} // namespace trapdoor

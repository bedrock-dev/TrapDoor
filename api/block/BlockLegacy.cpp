//
// Created by xhy on 2020/12/16.
//

#include <vector>
#include "BlockLegacy.h"
#include "lib/mod.h"
#include "lib/SymHook.h"

namespace trapdoor {
    using namespace SymHook;

    std::string BlockLegacy::getDebugText() {
        std::vector<std::string> vector;
        SYM_CALL(
                void(*)(BlockLegacy * , std::vector<std::string> &),
                MSSYM_MD5_794b421b4bf67101f7418cd0d78bad83,
                this, vector
        );
        int i = 0;
        for (const auto &str:vector) {
            printf("%d: %s ", i, str.c_str());
            ++i;
        }
        printf("\n");
        return std::string("text");
    }

    //获取某个特殊值状态下的方块对象
    Block *BlockLegacy::tryGetStateBlock(unsigned short state) {
        return SYM_CALL(
                Block * (*)(BlockLegacy * , unsigned short),
                MSSYM_B1QE25tryGetStateFromLegacyDataB1AE11BlockLegacyB2AAE13QEBAPEBVBlockB2AAA1GB1AA1Z,
                this, state
        );
    }

    BlockType BlockLegacy::getBlockID() {
        return (BlockType) *(short *) ((char *) this + 268);
    }
}


//
// Created by xhy on 2020/8/29.
//



#include "lib/pch.h"
#include <cstdint>
#include "Actor.h"
#include "graphics/BlockPos.h"
#include "block/Block.h"
using namespace SymHook;
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
    return original(self, player, block, pos, flag);
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
    original(self, pos, a3, a4);
}




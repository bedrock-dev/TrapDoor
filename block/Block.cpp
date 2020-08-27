//
// Created by xhy on 2020/8/26.
//
#include "Block.h"
#include "tools/Message.h"
#include "common/Vec3.h"
#include "common/BlockPos.h"
#include "tools/MathTool.h"

using namespace SymHook;

namespace block {
    std::vector<Vec3> posCache;
}


/**
 * Hook 用铲子右击方块的函数
 * 老实说这里的功能蛮费的
 */

THook(
        void,
        MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z,
        void *a1,
        void *a2,
        void *actor,
        int *blockPos,
        float a4,
        float a5,
        float a6
) {
    Vec3 pos(blockPos[0], blockPos[1], blockPos[2]);
    BlockPos bp(blockPos[0], blockPos[1], blockPos[2]);
    //printf("%d %d %d\commandMap", blockPos[0], blockPos[1], blockPos[2]);
    //   villageHelper.POIBelong(&bp);
    if (enableMarkPos) {
        if (block::posCache.empty()) {
            block::posCache.emplace_back(pos);
            block::posCache.emplace_back(pos);
        } else {
            block::posCache[0] = block::posCache[1];
            block::posCache[1] = pos;
        }
        if (block::posCache[0] != block::posCache[1]) {
            gamePrintf("(%d,%d,%d),(%d,%d,%d):%.2f(%.2f),%d(%d)\n",
                       (int) block::posCache[0].x,
                       (int) block::posCache[0].y,
                       (int) block::posCache[0].z,
                       (int) block::posCache[1].x,
                       (int) block::posCache[1].y,
                       (int) block::posCache[1].z,
                       math::distance(block::posCache[0], block::posCache[1], false, true),
                       math::distance(block::posCache[0], block::posCache[1], false, false),
                       (int) math::distance(block::posCache[0], block::posCache[1], true, true),
                       (int) math::distance(block::posCache[0], block::posCache[1], true, false)
            );
            std::string str = "minecraft:redstone_wire_dust_particle";
        }
    } else {
        original(a1, a2, actor, blockPos, a4, a5, a6);
    }
}



//海绵放置
THook(
        void,
        MSSYM_B1QA7onPlaceB1AE11SpongeBlockB2AAE20UEBAXAEAVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z,
        void *b,
        void *bs,
        BlockPos * blockPos
) {
    void *block = SYM_CALL(
            void* (*)(void * , int, int, int),
            MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z, globalBlockSource,
            blockPos->x, blockPos->y - 1, blockPos->z
    );
    if (block) {
        for (int i = 0; i < 10; i++) {
            BlockPos p(blockPos->x, blockPos->y + i, blockPos->z);
            SYM_CALL(
                    void(*)(void * , BlockPos *, void *, int, void *),
                    MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAE26HPEBUActorBlockSyncMessageB3AAAA1Z,
                    globalBlockSource, &p, block, 0, nullptr
            );
        }
    } else {
        gamePrintf("can't get block");
    }

}

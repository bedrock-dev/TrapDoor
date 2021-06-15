//
// Created by xhy on 2020/12/16.
//
#include "Block.h"
#include "BlockSource.h"
#include "world/Biome.h"
#include "world/LevelChunk.h"
#include "lib/Loader.h"
namespace trapdoor {

    Block *BlockSource::getBlock(int x, int y, int z) {
        return getBlock({x, y, z});
    }


    Block *BlockSource::getBlock(const BlockPos &blockPos) {
        return SymCall("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z", Block*, void*, BlockPos)(this, blockPos);
    }


    void BlockSource::setBlock(BlockPos *blockPos, Block *block) {
        SymCall("?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUAc"
            "torBlockSyncMessage@@@Z",
            void, void*, BlockPos*, void*, int, void*)(this, blockPos, block, 3, nullptr);
    }

    void BlockSource::updateNeighborsAt(const BlockPos *pos) {
        SymCall("?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z", void, BlockSource*,
            const BlockPos*)(this, pos);
    }


    void BlockSource::updateNeighbors(BlockPos *pos) {
        auto blockList = pos->getNeighbourPos();
        for (auto &p:blockList) {
            this->updateNeighborsAt(&p);
        }
    }

    Biome *BlockSource::getBiome(const BlockPos *pos) {
        return SymCall("?getBiome@BlockSource@@QEAAAEAVBiome@@AEBVBlockPos@@@Z", Biome*, BlockSource*, const BlockPos*)(this, pos);
    }

//    uint8_t BlockSource::getRawBrightness(const BlockPos *pos) {
//        uint8_t result = 255;
//        auto r = SYM_CALL(
//                uint8_t * (*)(BlockSource * , uint8_t *,
//                const BlockPos *, bool, bool),
//                MSSYM_B1QE16getRawBrightnessB1AE11BlockSourceB2AAA4QEBAB1QE12AUBrightnessB2AAE12AEBVBlockPosB3AAUA2N1B1AA1Z,
//                this,
//                &result,
//                pos,
//                true,
//                true
//        );
//        printf("%d %d\n", result, *r);
//        return result;
//
//    }
//
//    int BlockSource::getMaterial(const BlockPos *pos) {
//        return
//                *SYM_CALL(int * (*)(BlockSource * , int, int, int),
//                          MSSYM_B1QE11getMaterialB1AE11BlockSourceB2AAE16QEBAAEBVMaterialB2AAA3HHHB1AA1Z,
//                          this,
//                          pos->x,
//                          pos->y,
//                          pos->z
//                );
//    }

}

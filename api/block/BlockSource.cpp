//
// Created by xhy on 2020/12/16.
//
#include "Block.h"
#include "BlockSource.h"
#include "world/Biome.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "world/LevelChunk.h"

namespace trapdoor {
    using namespace SymHook;

    Block *BlockSource::getBlock(int x, int y, int z) {
        return SYM_CALL(
                Block* (*)(void * , int, int, int),
                MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z, this,
                x, y, z
        );
    }


    Block *BlockSource::getBlock(const BlockPos &blockPos) {
        return getBlock(blockPos.x, blockPos.y, blockPos.z);
    }

    void BlockSource::setBlock(BlockPos *blockPos, Block *block) {
        SYM_CALL(
                void(*)(void * , BlockPos *, void *, int, void *),
                MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAE26HPEBUActorBlockSyncMessageB3AAAA1Z,
                this, blockPos, block, 3, nullptr
        );
        // this->updateNeighborsAt(blockPos);
    }

    void BlockSource::updateNeighborsAt(const BlockPos *pos) {
//    dbg("update");
        SYM_CALL(
                void(*)(BlockSource * self,const BlockPos *pos),
                MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
                this, pos
        );
    }


    void BlockSource::updateNeighbors(BlockPos *pos) {
        auto blockList = pos->getNeighbourPos();
        for (auto &p:blockList) {
            this->updateNeighborsAt(&p);
        }
    }

    Biome *BlockSource::getBiome(const BlockPos *pos) {
        return
                SYM_CALL(
                        Biome*(*)(BlockSource * , const BlockPos *),
                        MSSYM_B1QA8getBiomeB1AE11BlockSourceB2AAE13QEAAAEAVBiomeB2AAE12AEBVBlockPosB3AAAA1Z,
                        this,
                        pos
                );
    }

    uint8_t BlockSource::getRawBrightness(const BlockPos *pos) {
        uint8_t result = 255;
        auto r = SYM_CALL(
                uint8_t *(*)(BlockSource * , uint8_t *,const BlockPos *, bool, bool),
                MSSYM_B1QE16getRawBrightnessB1AE11BlockSourceB2AAA4QEBAB1QE12AUBrightnessB2AAE12AEBVBlockPosB3AAUA2N1B1AA1Z,
                this,
                &result,
                pos,
                true,
                true
        );
        printf("%d %d\n", result, *r);
        return result;

    }

    int BlockSource::getMaterial(const BlockPos *pos) {
        return
                *SYM_CALL(int*(*)(BlockSource * , int, int, int),
                          MSSYM_B1QE11getMaterialB1AE11BlockSourceB2AAE16QEBAAEBVMaterialB2AAA3HHHB1AA1Z,
                          this,
                          pos->x,
                          pos->y,
                          pos->z
                );
    }

}

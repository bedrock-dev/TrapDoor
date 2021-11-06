//
// Created by xhy on 2020/12/16.
//
#include "BlockSource.h"

#include "Block.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "world/Biome.h"

namespace trapdoor {
    using namespace SymHook;

    Block *BlockSource::getBlock(int x, int y, int z) {
        return getBlock({x, y, z});
    }

    Block *BlockSource::getBlock(const BlockPos &blockPos) {
        return SYM_CALL(Block * (*)(void *, const BlockPos &),
                        BlockSource_getBlock_b39e5e5d, this, blockPos);
    }

    void BlockSource::setBlock(BlockPos *blockPos, Block *block) {
        SYM_CALL(void (*)(void *, int, int, int, Block *, int),

                 BlockSource_setBlock_71ce9a25, this, blockPos->x, blockPos->y,
                 blockPos->z, block, 3);
    }

    void BlockSource::updateNeighborsAt(const BlockPos *pos) {
        SYM_CALL(void (*)(BlockSource * self, const BlockPos *pos),
                 BlockSource_updateNeighborsAt_4c3f8cf7, this, pos);
    }

    void BlockSource::updateNeighbors(BlockPos *pos) {
        auto blockList = pos->getNeighbourPos();
        for (auto &p : blockList) {
            this->updateNeighborsAt(&p);
        }
    }

    Biome *BlockSource::getBiome(const BlockPos *pos) {
        return SYM_CALL(Biome * (*)(BlockSource *, const BlockPos *),
                        BlockSource_getBiome_967864de, this, pos);
    }
}  // namespace trapdoor

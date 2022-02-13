//
// Created by xhy on 2020/12/16.
//
#include "BlockSource.h"

#include "Block.h"
#include "graphics/BlockPos.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "world/Biome.h"

namespace trapdoor {
    using namespace SymHook;

    Block *BlockSource::getBlock(int x, int y, int z) {
        //        return getBlock({x, y, z});
        return SYM_CALL(Block * (*)(void *, int, int, int),
                        BlockSource_getBlock_6df88a51, this, x, y, z);
    }

    Block *BlockSource::getBlock(const BlockPos &pos) {
        return SYM_CALL(Block * (*)(void *, const BlockPos &),
                        BlockSource_getBlock_b39e5e5d, this, pos);
        //    return getBlock(pos.x, pos.y, pos.z);
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

    trapdoor::BlockPos2 LevelChunk::getPosition() {
        auto res = *SYM_CALL(trapdoor::BlockPos2 * (*)(LevelChunk *),
                             LevelChunk_getPosition_5b2499b2, this);
        return res;
    }
}  // namespace trapdoor
// using namespace SymHook;
// THook(trapdoor::Block *, BlockSource_getBlock_b39e5e5d,
//       trapdoor::BlockSource *source, const trapdoor::BlockPos &pos) {
//     return trapdoor::getBlockByID(trapdoor::DIAMOND_BLOCK);
// }

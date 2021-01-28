//
// Created by xhy on 2020/12/16.
//

#ifndef TRAPDOOR_BLOCKSOURCE_H
#define TRAPDOOR_BLOCKSOURCE_H

/*
 * 和世界交互的句柄，几乎所有行为都要经过这个东西，每个实体都有一份
 */
namespace trapdoor {
    class Block;

    class Biome;

    class BlockPos;

    class LevelChunk;


    class BlockSource {
    public:
        //获取某个位置的方块对象
        Block *getBlock(int x, int y, int z);

        //获取某个位置的方块对象
        Block *getBlock(const BlockPos &);

        //设置某个位置为某方块
        void setBlock(BlockPos *, Block *block);


        //更新某个方块
        void updateNeighborsAt(const BlockPos *pos);


        //更新position周围的六个方块
        void updateNeighbors(BlockPos *pos);

        //获取某个位置的群系
        Biome *getBiome(const BlockPos *pos);

        uint8_t getRawBrightness(const BlockPos *pos);

        int getMaterial(const BlockPos *pos);

        // LevelChunk *getLevelChunk(const ChunkPos &chunkPos);

    };

}
typedef trapdoor::BlockSource BlockSource;
#endif //TRAPDOOR_BLOCKSOURCE_H

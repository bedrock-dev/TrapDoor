//
// Created by xhy on 2020/12/16.
//

#ifndef TRAPDOOR_BLOCKSOURCE_H
#define TRAPDOOR_BLOCKSOURCE_H

#include "graphics/BlockPos.h"


class Block;

class Biome;

/*
 * 和世界交互的句柄，几乎所有行为都要经过这个东西，每个实体都有一份
 */
struct BlockSource {
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

};

#endif //TRAPDOOR_BLOCKSOURCE_H

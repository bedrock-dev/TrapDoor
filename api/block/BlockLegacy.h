//
// Created by xhy on 2020/12/16.
//

#ifndef TRAPDOOR_BLOCKLEGACY_H
#define TRAPDOOR_BLOCKLEGACY_H

#include <string>

class Block;

/*
 * 所有方块的父类
 */
namespace trapdoor {
    class BlockLegacy {
    public:
        //获取调试信息
        std::string getDebugText();

        //获取具有特殊值状态的方块对象
        Block *tryGetStateBlock(unsigned short state);

    };
}

#endif //TRAPDOOR_BLOCKLEGACY_H

//
// Created by xhy on 2021/1/3.
//

#ifndef MOD_BLOCKROTATIONHELPER_H
#define MOD_BLOCKROTATIONHELPER_H


#include "graphics/BlockPos.h"
#include "block/BlockSource.h"

namespace mod {
    class BlockRotationHelper {
        bool enable = true; //暂时默认开启
        inline bool inEnable() const { return this->enable; }

        inline void setAble(bool able) { this->enable = able; }

        void rotateSlabBlock(); //这个函数写半砖右键
    public:
        void rotate(trapdoor::BlockPos &pos, trapdoor::BlockSource *blockSource) const;

    };
}


#endif //MOD_BLOCKROTATIONHELPER_H

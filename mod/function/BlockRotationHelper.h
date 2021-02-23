//
// Created by xhy on 2021/1/3.
//

#ifndef MOD_BLOCKROTATIONHELPER_H
#define MOD_BLOCKROTATIONHELPER_H


#include "graphics/BlockPos.h"
#include "block/BlockSource.h"
#include "tools/noncopyable .h"

namespace mod {
    class BlockRotationHelper : noncopyable {
        bool enable = true;

    public:
        inline bool inEnable() const { return this->enable; }

        inline void setAble(bool able) { this->enable = able; }

        void rotate(trapdoor::BlockPos &pos, trapdoor::BlockSource *blockSource) const;

    };
}

#endif //MOD_BLOCKROTATIONHELPER_H

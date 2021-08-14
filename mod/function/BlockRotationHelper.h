//
// Created by xhy on 2021/1/3.
//

#ifndef MOD_BLOCKROTATIONHELPER_H
#define MOD_BLOCKROTATIONHELPER_H


#include "graphics/BlockPos.h"
#include "block/BlockSource.h"
#include "tools/noncopyable .h"
#include <set>
#include <functional>
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "graphics/Vec3.h"
#include "VanillaBlockType.h"
#include "Block.h"

namespace mod {

    struct RotationAction {
        std::set<trapdoor::BlockType> patterns;
        std::function<void(trapdoor::BlockSource *, trapdoor::Block *b, trapdoor::BlockPos &p, trapdoor::FACING facing,
                           Vec3 *v)> action;

        RotationAction(const std::set<trapdoor::BlockType> &set,
                       const std::function<void(trapdoor::BlockSource *, trapdoor::Block *, trapdoor::BlockPos &,
                                                trapdoor::FACING,
                                                Vec3 *)> &f) : patterns(set), action(f) {}

    };


    class BlockRotationHelper : noncopyable {
        bool enable = true;
        std::vector<RotationAction> actions;
    public:
        inline bool isEnable() const { return this->enable; }

        inline void setAble(bool able) { this->enable = able; }

        void rotate(trapdoor::BlockPos &pos, trapdoor::BlockSource *blockSource) const;

        void
        newRotate(trapdoor::BlockSource *blockSource, trapdoor::BlockPos &pos, trapdoor::FACING facing, Vec3 *v) const;

        void addActons();

    };
}

#endif //MOD_BLOCKROTATIONHELPER_H

//
// Created by xhy on 2021/1/3.
//

#ifndef MOD_BLOCKROTATIONHELPER_H
#define MOD_BLOCKROTATIONHELPER_H

#include "block/BlockSource.h"
#include "graphics/BlockPos.h"
#include "tools/noncopyable .h"
#include <set>
#include <functional>
#include <utility>
#include <algorithm>

namespace mod {

    typedef std::function<int(int, const trapdoor::Vec3 &, trapdoor::FACING)> RotateAction;

    struct BlockRotateAction {
        std::set<std::string> patterns;
        RotateAction action;

        BlockRotateAction(std::set<std::string> p, RotateAction act) : patterns(std::move(p)), action(std::move(act)) {}

        bool match(const std::string &name) const;
    };

    class BlockRotationHelper : noncopyable {
        bool enable = true;
        std::vector<BlockRotateAction> actionList;

        void addAction(const std::initializer_list<std::string> &patterns, const RotateAction &rotateAction);

    public:
        inline bool inEnable() const { return this->enable; }

        inline void setAble(bool able) { this->enable = able; }

        void init();

        void rotate(trapdoor::BlockPos &pos,
                    trapdoor::BlockSource *blockSource) const;

        void newRotate(trapdoor::BlockPos &pos, trapdoor::BlockSource *blockSource, const trapdoor::Vec3 &v,
                       trapdoor::FACING facing) const;
    };
}  // namespace mod

#endif  // MOD_BLOCKROTATIONHELPER_H

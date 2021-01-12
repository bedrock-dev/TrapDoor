//
// Created by xhy on 2020/12/27.
//

#ifndef MOD_HSAMANAGER_H
#define MOD_HSAMANAGER_H

#include <set>
#include "BDSMod.h"
#include "graphics/AABB.h"
#include "tools/noncopyable .h"

namespace mod {
    using namespace trapdoor;
    enum StructureType {
        SwampHut,
        OceanMonument,
        PillagerOutpost,
        NetherFortress
    };

    struct HsaInfo {
        StructureType type = PillagerOutpost;
        BoundingBox boundingBox{};
        int dimensionID = 0;

        bool operator<(const HsaInfo &rhs) const;
    };

    class HsaManager : noncopyable {
        bool enable;
        std::set<HsaInfo> hsaList;
        Tick gameTick;

    public:
        inline void insert(HsaInfo info) { this->hsaList.insert(info); }

        bool findHsa(const HsaInfo &hsaInfo);

        trapdoor::BlockPos findB(trapdoor::Actor *player);

        void draw(trapdoor::Actor *player);

        inline int clear() {
            int num = this->hsaList.size();
            this->hsaList.clear();
            return num;
        }

        void list(trapdoor::Actor *player);

        inline void setAble(bool able) { this->enable = able; };

        void tick();
    };
}  // namespace mod

#endif    // MOD_HSAMANAGER_H

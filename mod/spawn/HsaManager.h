//
// Created by xhy on 2020/12/27.
//

#ifndef MOD_HSAMANAGER_H
#define MOD_HSAMANAGER_H

#include "graphics/AABB.h"
#include  <set>
#include "BDSMod.h"

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


    class HsaManager {
        bool enable;
        std::set<HsaInfo> hsaList;
        Tick gameTick;
    public:
        inline void insert(HsaInfo info) { this->hsaList.insert(info); }

        bool findHsa(const HsaInfo &hsaInfo);

        inline void clear() { this->hsaList.clear(); }

        void list(trapdoor::Actor *player);

        inline void setAble(bool able) { this->enable = able; };

        void tick();
    };
}

#endif //MOD_HSAMANAGER_H

#pragma once

#include "lib/mod.h"
#include "lib/SymHook.h"
#include "common/BlockPos.h"
#include<set>

namespace village {

    class Village {
    public:
        int getPopulation();

        int getIronGolemNum();

        int getBedPOICount();

        int getWorkedVillagerNum();

        bool canSpawnIronGolem();

        BlockPos getCenter();

        float getRadius();
        AABB getBounds();
    };

    struct VillageHelper {
        VillageHelper() = default;

        std::set<Village *> villageList;

        void insert(Village *village);

        void clear();

        void draw();

        void list();
    };

    void villageTask();

    void listVillages();
}

#pragma once

#include "lib/mod.h"
#include "lib/SymHook.h"
#include "graphics/BlockPos.h"
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "graphics/AABB.h"
#include<set>


namespace mod {
    class Village {
    public:
        int getPopulation();

        int getIronGolemNum();

        int getBedPOICount();

        int getWorkedVillagerNum();

        bool canSpawnIronGolem();

        trapdoor::BlockPos getCenter();

        float getRadius();

        trapdoor::AABB getBounds();
    };

    class VillageHelper {
        bool enableShow = false;
        size_t gameTick = 0;
    public:

        inline void setVillageAble(bool able) { enableShow = able; };

        VillageHelper() = default;

        std::set<Village *> villageList;

        void insert(Village *village);

        void clear();

        void draw();

        void list(trapdoor::Actor *actor);

        void tick();
    };

}

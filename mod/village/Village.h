#pragma once

#include "lib/mod.h"
#include "lib/SymHook.h"
#include "graphics/BlockPos.h"
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "graphics/AABB.h"
#include "graphics/Vec3.h"
#include "graphics/Graphics.h"
#include<set>


namespace mod {


    class Village {
    public:
        int getPopulation();

        int getIronGolemNum();

        int getBedPOICount();

        int getWorkedVillagerNum();

        bool canSpawnIronGolem();

        trapdoor::Vec3 getCenter();

        float getRadius();

        trapdoor::AABB getBounds();
    };


    class VillageWithColor {
    public:
        Village *village;
        trapdoor::GRAPHIC_COLOR color;

        bool operator<(const VillageWithColor &rhs) const;

        void setRandomColor();
    };


    class VillageHelper {
        bool enableShow = false;
        size_t gameTick = 0;
    public:


        inline void setVillageShowAble(bool able) { enableShow = able; };

        VillageHelper() = default;

        std::set<VillageWithColor> villageList;

        void insert(const VillageWithColor &vw);

        void clear();

        void draw();

        void list(trapdoor::Actor *actor);

        void tick();
    };

}

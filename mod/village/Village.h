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
#include "tools/noncopyable .h"

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

        trapdoor::AABB getPOIRange();

        trapdoor::AABB getGolemSpawnArea();

        trapdoor::AABB getBounds();
    };


    class VillageWithColor {
    public:
        Village *village;
        trapdoor::GRAPHIC_COLOR color;

        bool operator<(const VillageWithColor &rhs) const;

        void setRandomColor();
    };

    struct VillageHelperConfig {
        trapdoor::GRAPHIC_COLOR boundColor = GRAPH_COLOR::BLUE;
        trapdoor::GRAPHIC_COLOR spawnColor = GRAPH_COLOR::GREEN;
        trapdoor::GRAPHIC_COLOR poiQueryColor = GRAPH_COLOR::WHITE;
        std::string centerParticle = "minecraft:heart_particle";
    };

    class VillageHelper : noncopyable {
        VillageHelperConfig villageHelperConfig;
        bool showBounds = false; //村庄边界
        bool showPOIRange = false; //poi查询范围
        bool showGolemSpawnArea = false; //铁傀儡刷出范围
        bool showVillageCenter = false; //显示村庄中心
        size_t gameTick = 0;
    public:
        inline void setShowBound(bool able) { showBounds = able; }

        inline void setShowPOIRange(bool able) { showPOIRange = able; }

        inline void setShowGolemSpawnArea(bool able) { showGolemSpawnArea = able; }

        inline void setShowVillageCenter(bool able) { showVillageCenter = able; }

        VillageHelper() = default;

        std::set<VillageWithColor> villageList;

        void insert(const VillageWithColor &vw);

        void clear();

        void draw();

        void list(trapdoor::Actor *actor);

        inline void setConfig(const VillageHelperConfig &config) {
            this->villageHelperConfig = config;
        }

        void tick();
    };

}

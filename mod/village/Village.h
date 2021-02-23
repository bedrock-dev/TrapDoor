#pragma once

#include "lib/mod.h"
#include "lib/SymHook.h"
#include "graphics/BlockPos.h"
#include "entity/Actor.h"
#include "graphics/AABB.h"
#include "world/Level.h"
#include "graphics/Vec3.h"
#include "graphics/Graphics.h"
#include<set>
#include "tools/noncopyable .h"
#include "commands/CommandManager.h"

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

        void printAllPOIs();

        void showVillagerStatus();

        void showTimeStamp();

        std::string getDebugInfo();

        bool printVillagerInfo(trapdoor::Actor *player, trapdoor::Actor *actor);

        void removeAllTags();

    };


    //这个其实蛮冗余的，懒得删了
    class VillageWithColor {
    public:
        Village *village;
        trapdoor::GRAPHIC_COLOR color;

        bool operator<(const VillageWithColor &rhs) const;
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
        bool showDwellerStatus = false;
        size_t gameTick = 0;
    public:
        inline void setShowBound(bool able) { showBounds = able; }

        inline void setShowPOIRange(bool able) { showPOIRange = able; }

        inline void setShowGolemSpawnArea(bool able) { showGolemSpawnArea = able; }

        inline void setShowVillageCenter(bool able) { showVillageCenter = able; }

        inline void setShowDwellerStatus(bool able) {
            showDwellerStatus = able;
            //关闭头顶显示后移除所有的命名
            if (!able)this->removeAllNameTag();
        }

        inline bool getShowDwellerStatus() const { return showDwellerStatus; }

        VillageHelper() = default;

        std::set<VillageWithColor> villageList;

        void insert(const VillageWithColor &vw);

        void clear();

        void draw();

        void showVillagerStatus();

        void list(trapdoor::Actor *actor);

        void test();

        void printNearestVillageInfo(trapdoor::Actor *player, const trapdoor::Vec3 &pos);

        inline void setConfig(const VillageHelperConfig &config) {
            this->villageHelperConfig = config;
        }

        void tick();

        void printDwellerInfo(trapdoor::Actor *player, trapdoor::Actor *actor);

        void removeAllNameTag();

        void registerCommand(trapdoor::CommandManager &commandManager);

    };

}

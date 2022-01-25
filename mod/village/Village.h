#pragma once

#include <set>

#include "commands/CommandManager.h"
#include "entity/Actor.h"
#include "graphics/AABB.h"
#include "graphics/BlockPos.h"
#include "graphics/Particle.h"
#include "graphics/Vec3.h"
#include "lib/Remotery.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/noncopyable .h"
#include "world/Level.h"

namespace mod {

    class Village {
       public:
        //获取当前村庄人口数
        int getPopulation();
        //获取当前村庄铁傀儡数
        int getIronGolemNum();

        //获取当前村庄的POI数量
        int getBedPOICount();

        //获取当天工作过的村民数量
        //! 不可用
        int getWorkedVillagerNum();

        //当前是否能生成铁傀儡
        bool canSpawnIronGolem();

        //获取村庄中心
        trapdoor::Vec3 getCenter();

        //获取村庄半径
        float getRadius();

        //获取POI查询范围
        trapdoor::AABB getPOIRange();

        //获取铁傀儡刷新区域
        trapdoor::AABB getGolemSpawnArea();

        //获取村庄边框
        trapdoor::AABB getBounds();

        //打印所有的POI
        void printAllPOIs();

        void showVillagerStatus(int vIdx);

        //显示TS值
        void showTimeStamp();

        //获取调试新型
        std::string getDebugInfo();

        //打印村庄详细新型
        bool printVillagerInfo(trapdoor::Actor *player, trapdoor::Actor *actor);

        //移除村民头顶标签
        void removeAllTags();

        //测试用函数
        void test();
    };

    struct VillageHelperConfig {
        trapdoor::GRAPHIC_COLOR boundColor = GRAPH_COLOR::BLUE;
        trapdoor::GRAPHIC_COLOR spawnColor = GRAPH_COLOR::GREEN;
        trapdoor::GRAPHIC_COLOR poiQueryColor = GRAPH_COLOR::WHITE;
        std::string centerParticle = "minecraft:heart_particle";
    };

    class VillageHelper : noncopyable {
        VillageHelperConfig villageHelperConfig;
        bool showBounds = false;          //村庄边界
        bool showPOIRange = false;        // poi查询范围
        bool showGolemSpawnArea = false;  //铁傀儡刷出范围
        bool showVillageCenter = false;   //显示村庄中心
        bool showDwellerStatus = false;
        size_t gameTick = 0;

        std::set<mod::Village *> villageList;

       public:
        inline void setShowBound(bool able) { showBounds = able; }

        inline void setShowPOIRange(bool able) { showPOIRange = able; }

        inline void setShowGolemSpawnArea(bool able) {
            showGolemSpawnArea = able;
        }

        inline void setShowVillageCenter(bool able) {
            showVillageCenter = able;
        }

        inline void setShowDwellerStatus(bool able) {
            showDwellerStatus = able;
            //关闭头顶显示后移除所有的命名
            if (!able) {
                this->removeAllNameTag();
            }
        }

        inline bool getShowDwellerStatus() const { return showDwellerStatus; }

        VillageHelper() = default;

        void insert(Village *v);

        void clear();

        void draw();

        void showVillagerStatus();

        void list(trapdoor::Actor *actor);

        void test();

        //打印最近的村民信息
        void printNearestVillageInfo(trapdoor::Actor *player,
                                     const trapdoor::Vec3 &pos);

        //初始化配置信息
        inline void setConfig(const VillageHelperConfig &config) {
            this->villageHelperConfig = config;
        }

        //更新
        void tick();

        //打印居民信息
        void printDwellerInfo(trapdoor::Actor *player, trapdoor::Actor *actor);

        //移除所有头顶标签
        void removeAllNameTag();

        //注册village命令
        void registerCommand(trapdoor::CommandManager &commandManager);
    };

}  // namespace mod

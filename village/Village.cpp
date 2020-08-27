//
// Created by xhy on 2020/8/25.
//
#include "Village.h"
#include "common/Common.h"
#include "tools/Message.h"
#include "tools/Particle.h"

using namespace SymHook;
//village tick

namespace village {
    const size_t BOUND_OFFSET = 104;
    const size_t POPULATION_OFFSET = 22;
    const size_t GOLEM_NUM_OFFSET = 30;
    VillageHelper villageHelper; //NOLINT

    //get village population
    int getPopulation(void *village) {
        return (int) *((int64_t *) village + POPULATION_OFFSET);
    }

    //get village owned iron golem num
    int getIronGolemNum(void *village) {
        return (int) *((int64_t *) village + GOLEM_NUM_OFFSET);
    }

    //get village owned bed poi count(max is villager num + 32)
    int getBedPOICount(void *village) {
        return
                SYM_CALL(
                        int(*)(void * ),
                        MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ,
                        village
                );
    }

    //get worked villager num
    int getWorkedVillagerNum(void *village) {
        auto timeOfDay = *(reinterpret_cast<int64_t *>(village) + 60) - 24000;
        auto begin = *(reinterpret_cast<int64_t *>(village) + 85);
        auto end = *(reinterpret_cast<int64_t *>(village) + 86);
        int num;
        for (num = 0; begin != end; begin += 16) {
            if (*(int64_t *) (begin + 8) > timeOfDay)
                ++num;
        }
        return num;
    }

    //check can spawn iron golem
    bool canSpawnIronGolem(int population, int golemNum, int workedNum, int bedNUm) {
        int max = 20 > population ? 20 : population;
        return (float) workedNum > population * 0.75 && golemNum < population / 10 && bedNUm > max;
    }

    //get village center
    Vec3 getVillageCenter(void *village) {
        Vec3 center = {
                (*((float *) village + BOUND_OFFSET + 3) + *((float *) village + BOUND_OFFSET)) / 2,
                (*((float *) village + BOUND_OFFSET + 4) + *((float *) village + BOUND_OFFSET + 1)) / 2,
                (*((float *) village + BOUND_OFFSET + 5) + *((float *) village + BOUND_OFFSET + 2)) / 2,
        };
        return center;
    }

    //get village bounds
    AABB getVillageBound(void *village) {
        Vec3 p1 = {*((float *) village + BOUND_OFFSET + 3),
                   *((float *) village + BOUND_OFFSET + 4),
                   *((float *) village + BOUND_OFFSET + 5)};
        Vec3 p2 = {*((float *) village + BOUND_OFFSET),
                   *((float *) village + BOUND_OFFSET + 1),
                   *((float *) village + BOUND_OFFSET + 2)};
        AABB aabb(p2, p1);
        return aabb;
    }

    //get village radius
    float getVillageRadius(void *village) {
        if (!village)return -1.0;
        return SYM_CALL(
                float(*)(void * ),
                MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ,
                village
        );
    }

    int villageInterval = 0;

    void villageTask() {
        if (villageInterval % 15 == 0 && enableVillageShow) {
            villageHelper.draw();
        }
        if (villageInterval % 100 == 0) {
            villageHelper.clear();
        }
        villageInterval = (villageInterval + 1) % 300;
    }

    void listVillages() {
        villageHelper.list();
    }

    void VillageHelper::clear() {
        villageList.clear();
    }

    void VillageHelper::insert(void *village) {
        villageList.insert(village);
    }

    void VillageHelper::draw() {
        if (enableVillageShow) {
            std::string borderParticleType = "minecraft:dragon_breath_trail";
            std::string centerParticleType = "minecraft:heart_particle";
            for (auto village:villageList) {
                if (village) {
                    spawnRectangleParticle(getVillageBound(village), borderParticleType);
                    Vec3 center = getVillageCenter(village);
                    spawnParticle(center, centerParticleType);
                }
            }
        }
    }

    void VillageHelper::list() {
        gamePrintf("here are all the ticking villages:\n");
        int i = 0;
        for (auto village : villageList) {
            if (village) {
                auto aabb = getVillageBound(village);
                auto center = getVillageCenter(village);
                auto population = getPopulation(village);
                auto bedNum = getBedPOICount(village);
                auto golem = getIronGolemNum(village);
                auto worked = getWorkedVillagerNum(village);
                gamePrintf("v§2%d§b: [%d,%d,%d],[%d,%d,%d]§rc:§b[%d,%d,%d]§rr:§2%.2f p:%d/%d g:%d b:%d  %d\n",
                           i,
                           (int) aabb.p1.x,
                           (int) aabb.p1.y,
                           (int) aabb.p1.z,
                           (int) aabb.p2.x,
                           (int) aabb.p2.y,
                           (int) aabb.p2.z,
                           (int) center.x,
                           (int) center.y,
                           (int) center.z,
                           getVillageRadius(village),
                           worked,
                           population,
                           golem,
                           bedNum,
                           canSpawnIronGolem(population, golem, worked, bedNum)
                );
                i++;
            }
        }
    }
}
THook(
        void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
        void *vill, void *tick, void * blockSource
) {
    original(vill, tick, blockSource);
    village::villageHelper.insert(vill);
}

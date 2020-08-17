#pragma once

#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include <strstream>
#include<set>


/*
 * 这里是所有村庄相关的实现
 */

using namespace SymHook;

int getPopulation(void *village) {
    return *((int64_t *) village + 22);
}

//*((_QWORD *)village + 30)
int getIronGolemNum(void *village) {
    return *((int64_t *) village + 30);
}

int getBedCount(void *village) {
    return
            SYM_CALL(
                    int(*)(void * ),
                    MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ,
                    village
            );
}


int getWorkedNum(void *village) {
    auto timeOfDay = *(reinterpret_cast<int64_t *>(village) + 60) - 24000;
    auto begin = *(reinterpret_cast<int64_t *>(village) + 85);
    auto end = *(reinterpret_cast<int64_t *>(village) + 86);
    int num = 0;
    for (num = 0; begin != end; begin += 16) {
        if (*(int64_t *) (begin + 8) <= timeOfDay)
            ++num;
    }
    return num;
}

//铁傀儡刷出
bool canSpawnIronGolem(int population, int golemNum, int workedNum, int bedNUm) {
    int max = 20 > population ? 20 : population;
    return (float) workedNum > population * 0.75 && golemNum < population / 10 && bedNUm > max;
}


Vec3 getVillageCenter(void *village) {
    Vec3 center = {
            (*((float *) village + 107) + *((float *) village + 104)) / 2,
            (*((float *) village + 108) + *((float *) village + 105)) / 2,
            (*((float *) village + 109) + *((float *) village + 106)) / 2,
    };
    return center;
}

AABB getVillageBound(void *village) {
    Vec3 p1 = {*((float *) village + 107), *((float *) village + 108), *((float *) village + 109)};
    Vec3 p2 = {*((float *) village + 104), *((float *) village + 105), *((float *) village + 106)};
    AABB aabb(p2, p1);
    return aabb;
}

float getVillageRadius(void *village) {
    if (!village)return -1.0;
    return SYM_CALL(
            float(*)(void * ),
            MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ,
            village
    );
}

struct VillageHelper {
    VillageHelper() = default;

    std::set<void *> villageList;

    void insert(void *village) {
        villageList.insert(village);
    }

    void clear() {
        villageList.clear();
    }

    void draw() {
        if (enableVillageShow) {
            std::string borderParticleType = "trapdoor:redplane";
            std::string centerParticleType = "minecraft:heart_particle";
            for (auto village:villageList) {
                if (village) {
                    spawnRectangleParticle(getVillageBound(village), borderParticleType);
                    Vec3 center = getVillageCenter(village);
                    float pos[3] = {center.x, center.y + 0.3f, center.z};
                    spawnParticle(pos, centerParticleType);
                }
            }
        }
    }

    void list() {
        gamePrintf("here are all the ticking villages:\n");
        int i = 0;
        for (auto village : villageList) {
            if (village) {
                auto aabb = getVillageBound(village);
                auto center = getVillageCenter(village);
                auto population = getPopulation(village);
                auto bedNum = getBedCount(village);
                auto golem = getIronGolemNum(village);
                auto worked = getWorkedNum(village);
                gamePrintf("v§2%d§b: [%d,%d,%d],[%d,%d,%d]§rc:§b[%d,%d,%d]§rr:§2%.2f  p:%d/%d g:%d b:%d\n",
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
                        // worked,
                           population,
                           golem,
                           bedNum
                        //   canSpawnIronGolem(population, golem, worked, bedNum)
                );
                i++;
            }
        }
    }


    //这功能先鸽了
};

//THook(void,
//      MSSYM_B1QA4tickB1AE14VillageManagerB2AAE13QEAAXAEBUTickB3AAAA1Z,
//      void *manager,
//      void * tick
//) {
//    if (!villageManager)villageManager = manager;
//    original(manager, tick);
//}

//THook(
//        bool,
//        MSSYM_B1QE12isVillagePOIB1AA7VillageB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z,
//        void *bs,
//        int32_t * blockPos
//) {
//    printf("update POI at (%d %d %d) blockSource: %d\n", blockPos[0], blockPos[1], blockPos[2],
//           globalBlockSource == bs);
//    return original(bs, blockPos);
//}

VillageHelper villageHelper;


//
THook(
        void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
        void *vill, void *tick, void * blockSource
) {
    original(vill, tick, blockSource);
    villageHelper.insert(vill);
}


int villageInterval = 0;

void villageTask() {
    if (villageInterval % 40 == 0 && enableVillageShow) {
        villageHelper.draw();
    }
    if (villageInterval % 100 == 0) {
        villageHelper.clear();
    }
    villageInterval = (villageInterval + 1) % 200;
}


void listVillages() {
    villageHelper.list();
}

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
            std::string borderParticleType = "minecraft:totem_particle";
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
                gamePrintf("v§2%d§b: [%d,%d,%d],[%d,%d,%d]§rc:§b[%d,%d,%d]§rr:§2%.2f \n",
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
                           getVillageRadius(village)
                );
                i++;
            }
        }
    }


    //这功能先鸽了
//    void POIBelong(BlockPos *pos) {
//        auto vec = pos->toVec3();
//        for (auto village:villageList) {
//            if (village && globalBlockSource) {
//                auto result = SYM_CALL(
//                        bool(*)(void * village, void * bs, void * bp),
//                        MSSYM_B1QE12isVillagePOIB1AA7VillageB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z,
//                        village,
//                        globalBlockSource,
//                        pos
//                );
//                if (result) {
//                    auto center = getVillageCenter(village);
//                    gamePrintf("this POI belongs to center:§b[%d %d %d]", center.x, center.y, center.z);
//                    //  std::string particleName = "minecraft:redstone_wire_dust_particle";
//                    //  spawnLineParticle(&vec, &center, particleName);
//                    return;
//                }
//            }
//        }
//        gamePrintf("it don't belong to any village");
//    }
};

VillageHelper villageHelper;

THook(
        void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
        void *vill, void *tick, void * blockSource
) {
    original(vill, tick, blockSource);
    villageHelper.insert(vill);
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

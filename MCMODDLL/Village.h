#pragma once

#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"


#include<set>

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
            std::string type = "minecraft:redstone_ore_dust_particle";
            for (auto village:villageList) {
                if (village) {
                    spawnRectangleParticle(getVillageBound(village), type);
                    Vec3 center = getVillageCenter(village);
                    float pos[3] = {center.x, center.y + 0.2f, center.z};
                    spawnParticle(pos, type);
                }
            }
        }
    }

    void list() {
        int i = 0;
        gamePrintf("here are all the ticking villages:\n");
        for (auto village : villageList) {
            if (village) {
                auto aabb = getVillageBound(village);
                auto center = getVillageCenter(village);
                char msg[512];
                gamePrintf("v %d: b: [(%d,%d,%d),(%d,%d,%d) c: (%d,%d,%d) r:%.2f \n",
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
                gamePrintf(msg);
                ++i;
            }
        }
    }
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
    if (villageInterval % 8 == 0) {
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

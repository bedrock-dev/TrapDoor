#pragma once

#include "lib/mod.h"
#include "lib/SymHook.h"
#include<set>
namespace village {


    int getPopulation(void *village);

    int getIronGolemNum(void *village);

    int getBedPOICount(void *village);


    int getWorkedVillagerNum(void *village);

    bool canSpawnIronGolem(int population, int golemNum, int workedNum, int bedNUm);


    Vec3 getVillageCenter(void *village);

    AABB getVillageBound(void *village);

    float getVillageRadius(void *village);

    struct VillageHelper {
        VillageHelper() = default;

        std::set<void *> villageList;

        void insert(void *village);

        void clear();

        void draw();

        void list();
    };




    void villageTask();

    void listVillages();
}
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
//    printf("update POI at (%d %d %d) blockSource: %d\commandMap", blockPos[0], blockPos[1], blockPos[2],
//           globalBlockSource == bs);
//    return original(bs, blockPos);
//}
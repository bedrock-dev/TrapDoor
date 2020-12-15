//
// Created by xhy on 2020/8/25.
//

#include "Spawn.h"
#include "tick/GameTick.h"
#include "level/Dimension.h"
#include "graphics/AABB.h"
#include "common/Trapdoor.h"

using namespace SymHook;

int getMobCount(void *sp) {
    if (!sp)return -1;
    return *(reinterpret_cast<UINT32 *>(sp) + 48);
}

THook(
        void,
        MSSYM_B2QUE17spawnStructureMobB1AA7SpawnerB2AAE20AEAAXAEAVBlockSourceB2AAE12AEBVBlockPosB2AAE25AEBUHardcodedSpawningAreaB1AE10LevelChunkB2AAE19AEBVSpawnConditionsB3AAAA1Z,
        void *spawner,
        void *blockSource,
        void *blockPos,
        BoundingBox *hsa,
        void * spawnconditions
) {
    auto min = hsa->minPos;
    auto max = hsa->maxPos;
    auto &globalHsaList = getHardcodedSpawnAreas();
    globalHsaList.insert({min, max});
   // printf("%d %d %d -- %d,%d %d\n", min.x, min.y, min.z, max.x, max.y, max.z);
    original(spawner, blockSource, blockPos, hsa, spawnconditions);
}


//THook(
//        int,
//        MSSYM_B1QE13getSpawnCountB1AE13MobSpawnRulesB2AAE24QEBAHAEBVSpawnConditionsB2AAE15AEAVBlockSourceB2AAE10AEAVRandomB2AAE20AEBUMobSpawnHerdInfoB3AAAA1Z,
//        void *mobSpawnRules,
//        char *spawnConditions,
//        BlockSource *blockSource,
//        void *random,
//        void * Herdinfo
//) {
//
//    // if (tick::tickStatus != tick::Normal && tick::tickStatus != tick::Wrap) {
////    int val = original(mobSpawnRules, spawnConditions, blockSource, random, Herdinfo);
////    if (val == 0) {
////        printf("get a zero herd\n");
////    }
//
////
////
////    printf("\n");
////    tick::freezeTick();
////    return 1;
////    } else {
//    int val = original(mobSpawnRules, spawnConditions, blockSource, random, Herdinfo);
//    if (val == 0) {
//        printf("get a zero number spawn!\n");
//    }
//    return val;
//    //    }
//    // return 1;
//    // return 1;
//}
//
//THook(
//        void *,
//        MSSYM_B1QE13getMobToSpawnB1AE11BlockLegacyB2AAE22UEBAPEBVMobSpawnerDataB2AAE19AEBVSpawnConditionsB2AAE15AEAVBlockSourceB3AAAA1Z,
//        BlockLegacy *legacy,
//        SpawnConditions *conditions,
//        BlockSource * blockSource
//) {
//    auto block = blockSource->getBlock(*conditions->position());
//
////    printf("%s : p (%d %d %d)  s:%d  u:%d w:%d l:%d\n",
////           block->getName().c_str(),
////           conditions->position()->x,
////           conditions->position()->y,
////           conditions->position()->z,
////           conditions->isSurface(),
////           conditions->isUnderGround(),
////           conditions->isInWater(),
////           conditions->isInLava()
////    );
////    auto var = conditions->isSurface() ? 0 : 1;
////    auto var2 = 0;
////    if (conditions->isInWater()) {
////        var2 = 1;
////    }
////    if (conditions->isInLava()) {
////        var2 = 2;
////    }
////
////    int sv = var * 3 + var2 + 1;
////
////    BlockPos pos = {
////            conditions->position()->x,
////            conditions->position()->y - 1,
////            conditions->position()->z,
////    };
////    if (conditions->isInWater() || conditions->isInLava()) {
////        auto b = blockSource->getBlock(pos);
////        blockSource->setBlock(&pos,
////                              b->getLegacy()->tryGetStateBlock(sv));
////
////    } else {
////
////        blockSource->setBlock(conditions->position(),
////                              block->getLegacy()->tryGetStateBlock(sv));
////    }
//
//    return original(legacy, conditions, blockSource);
//}
//
//THook(
//        bool,
//        MSSYM_B2QUE12popCapAllowsB1AA7SpawnerB2AAA4AEBAB1UE14NAEBVDimensionB2AAE18AEBVMobSpawnerDataB3AAUA2N2B1AA1Z,
//        void *spawner,
//        Dimension *dimension,
//        void *data,
//        bool a,
//        bool b
//) {
//    bool val = original(spawner, dimension, data, a, b);
//    if (!val) {
//        printf("dimension base type  limit \n");
//    }
//    return val;
//    //  return true;
//}
//
////THook(
////        int,
////        MSSYM_B1QE17getActorSpawnPoolB1AE19ActorSpawnRuleGroupB2AAE34QEBAHAEBUActorDefinitionIdentifierB3AAAA1Z,
////        void *spawnRulesGroup,
////        ActorDefinitionIdentifier * actorID
////) {
////    int val = original(spawnRulesGroup, actorID);
////    printf("%s %d\n",actorID->getName().c_str(),val);
////    return val;
////
////}
//
//THook(
//        int,
//        MSSYM_B1QE11getDelayEndB1AE19ActorSpawnRuleGroupB2AAA6QEBAHVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
//        void *group,
//        void * mob
//) {
//    int val = original(group, mob);
//    if (val != 0) {
//        printf("spawn delay enable\n %d\n", val);
//    }
//    return val;
//}
//
//THook(int,
//      MSSYM_B2QUE19handlePopulationCapB1AA7SpawnerB2AAE23AEAAHPEBVMobSpawnerDataB2AAE19AEBVSpawnConditionsB2AAA1HB1AA1Z,
//      void *spawner,
//      void *data,
//      void *conditions,
//      int spawnCount
//) {
//    int val = original(spawner, data, conditions, spawnCount);
//    if (val == 0) {
//        printf("type limit:  %d == > %d\n", spawnCount, val);
//    }
//    return val;
//}


BlockPos *SpawnConditions::position() {
    return reinterpret_cast<BlockPos *>(CHAR(this) + 20);
}

bool SpawnConditions::isInWater() {
    return *(CHAR(this) + 1) == 1;
}

int SpawnConditions::bright() {
    return *reinterpret_cast<int *>((CHAR(this) + 16));
}

bool SpawnConditions::isInLava() {
    return *(CHAR(this) + 2) == 1;
}

bool SpawnConditions::isSurface() {
    return *(CHAR(this)) == 1;
}

bool SpawnConditions::isUnderGround() {
    return *(CHAR(this) + 3) == 1;
}

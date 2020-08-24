//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_ACTORHOOK_H
#define TRAPDOOR_ACTORHOOK_H

#include "lib/pch.h"
#include "lib/mod.h"
#include "Actor.h"
#include "lib/SymHook.h"

namespace SymHook {
    THook(
            void,
            MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z,
            void *p1,
            void * p2
    ) {
        if (p1 && p2) {
            // if (getActorName(p2) == "minecraft:villager_v2<>") {
            original(p1, p2);
            if (p2) {
                std::string infoText;
                SYM_CALL(void(*)(void * mob, std::string &),
                         MSSYM_B1QE14buildDebugInfoB1AA3MobB2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
                         p2, infoText
                );

                SYM_CALL(
                        void(*)(void * actor,
                        const std::string &str),
                        MSSYM_B1QE10setNameTagB1AA5ActorB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
                        p2,
                        infoText
                );
            }
        }
    }

    THook(
            void,
            MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z,
            void *sp,
            void *bs,
            char *actorId,
            void *actor,
            Vec3 *pos,
            bool a6,
            bool a7,
            bool a8
    ) {
        // printf("spawn %s at %f %f %f \commandMap", actorIDtoString(actorId).c_str(), pos->x, pos->y, pos->z);
        if (mobSpawnCounterStart && pos) {
            auto mobName = spawn::actorIDtoString(actorId);
            Vec3 vec(pos->x, pos->y, pos->z);
            spawn::mobCounterList[mobName].emplace_back(vec);
        }
        original(sp, bs, actorId, actor, pos, a6, a7, a8);
    }

    THook(
            void,
            MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ,
            void * exp
    ) {
        if (enableExplosion) {
            original(exp);
        }
    }
}

#endif //TRAPDOOR_ACTORHOOK_H

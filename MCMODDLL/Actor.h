#pragma once

#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include "Spawn.h"
#include <vector>
#include <map>

using namespace SymHook;


std::vector<std::string> getActorText(void *actor) {
    std::vector<std::string> info;
    SYM_CALL(void(*)(void * , std::vector<std::string> &),
             MSSYM_MD5_f04fad6bac034f1e861181d3580320f2,
             actor, info);
    return info;
}

//0: Entity type: minecraft:villager_v2<>
std::string getActorName(void *actor) {
    return actor ? getActorText(actor)[0].substr(13) : "null";
}


void sendInfo() {
    auto mobNum = getMobCount(spawner);
    char str[64];
    sprintf_s(str, "total mob count: %d", mobNum);
    gamePrintf(str);
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


THook(
        void,
        MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z,
        void *p1,
        void * p2
) {
    if (p1 && p2) {
        if (getActorName(p2) == "minecraft:villager_v2<>") {
            std::string infoText;
            SYM_CALL(void(*)(void * villager, std::string &),
                     MSSYM_B1QE14buildDebugInfoB1AE10VillagerV2B2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
                     p2, infoText
            );
            printf("%s", infoText.c_str());
            gamePrintf(infoText);
        }

    }
}

std::string actorIDtoString(char *actorID) {
    auto str = reinterpret_cast<std::string *>(actorID + 32);
    return std::string(*str);
}

std::map<std::string, std::vector<Vec3>> mobCounterList;

THook(
        void,
        MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z,
        void *sp,
        void *bs,
        char *id,
        void *actor,
        Vec3 *pos,
        bool a6,
        bool a7,
        bool a8
) {
    // printf("spawn %s at %f %f %f \n", actorIDtoString(id).c_str(), pos->x, pos->y, pos->z);
    original(sp, bs, id, actor, pos, a6, a7, a8);
    if (mobSpawnCounterStart) {
        auto mobName = actorIDtoString(id);
        mobCounterList[mobName].emplace_back(*pos);
    }
}

void startSpawnCounter() {
    if (mobSpawnCounterStart) {
        error("this command can only be run after the counter end");
    } else {
        mobCounterList.clear();
        mobSpawnCounterStart = true;
        gamePrintf("counter start");
    }
}

void endSpawnerCounter() {
    if (!mobSpawnCounterStart) {
        error("this command can only be run after the counter start");
    } else {
        mobSpawnCounterStart = false;
        gamePrintf("counter end");
    }
}

void clearSpawnCounter() {
    if (mobSpawnCounterStart) {
        error("this command can only be run after the counter end");
        return;
    } else {
        mobCounterList.clear();
        gamePrintf("counter cleared");
    }
}

void spawnAnalysis(std::string &type) {
    if (type == "null") {
        std::map<std::string, size_t> mobList;
        std::map<int, int> heightMap;
        size_t totalNum = 0;
        for (const auto &item:mobCounterList) {
            mobList[item.first] = item.second.size();
            totalNum += item.second.size();
            for (auto vec : item.second)
                heightMap[vec.y]++;
        }
        for (auto &i: mobList)
            gamePrintf("%s : §2%d\n", i.first.c_str(), i.second);
        gamePrintf("----------");
        for (auto &i: heightMap)
            gamePrintf("§2%d: §2%d", i.first, i.second);

    } else {
        auto iter = mobCounterList.find(type);
        if (iter == mobCounterList.end()) {
            gamePrintf("no mob type named %s", type.c_str());
        } else {
            gamePrintf("function developing\n");
        }
    }
}

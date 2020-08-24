#pragma once

#include "common/Common.h"
#include "lib/pch.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "spawn/Spawn.h"
#include <vector>
#include <map>
#include "../spawn/Spawn.h"
#include "tools/Message.h"

/**
 * todo: need re write
 */
namespace spawn {

    std::map<std::string, std::vector<Vec3>> mobCounterList;//NOLINT

    Vec3 *getPos(void *actor) {
        return SYM_CALL(
                Vec3*(*)(void * ),
                MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ,
                actor
        );
    }

    std::string actorIDtoString(char *actorID) {
        auto str = reinterpret_cast<std::string *>(actorID + 32);
        return std::string(*str);
    }

    std::vector<std::string> getActorText(void *actor) {
        std::vector<std::string> info;
        if (!actor)return info;
        SYM_CALL(void(*)(void * , std::vector<std::string> &),
                 MSSYM_MD5_f04fad6bac034f1e861181d3580320f2,
                 actor, info);
        return info;
    }

    void sendMobInfo() {
        int mobNum = getMobCount(globalSpawner);
        char str[64];
        sprintf_s(str, "total mob count: %d", mobNum);
        gamePrintf(str);
    }


    void startSpawnCounter() {
        if (mobSpawnCounterStart) {
            error("it's already start some ticks before");
        } else {
            mobCounterList.clear();
            mobTickCounter = 0;
            mobSpawnCounterStart = true;
            gamePrintf("counter start, type ./spawner end to end the counter");
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

    void spawnAnalysis(std::string &type) {
        if (mobTickCounter == 0) {
            warning("no data");
            return;
        }
        if (type == "null") {
            std::map<std::string, size_t> mobList;
            std::map<int, int> heightMap;
            std::map<int, int> disMap;
            auto playerPos = getPos(globalPlayer);
            size_t totalNum = 0;
            for (const auto &item:mobCounterList) {
                mobList[item.first] = item.second.size();
                totalNum += item.second.size();

                for (auto vec : item.second) {
                    heightMap[(int) vec.y]++;
                    disMap[(int) math::distance(vec, *playerPos)]++;
                }
            }
            gamePrintf("total §2%d §r tick", mobTickCounter);
            for (auto &i: mobList)
                gamePrintf("%s : §2%d       §r(§2%.2f§r/h)\n", i.first.c_str(), i.second,
                           (float) i.second * 72000.0 / (float) mobTickCounter);
            gamePrintf("-------distance map---------");
            for (auto &i: heightMap)
                gamePrintf("[%d-%d]: §2%d", i.first, i.first + 1, i.second);
            gamePrintf("--------height map--------");
            for (auto &i: heightMap)
                gamePrintf("%d: §2%d", i.first, i.second);

        } else {

            auto iter = mobCounterList.find(type);
            if (iter == mobCounterList.end()) {
                gamePrintf("no mob type named %s", type.c_str());
            } else {
                gamePrintf("function developing\n");
            }
        }
    }

    std::string getActorName(void *actor) {
//#warning this func is hardcoded, it may need rewrite when update the game
        return actor ? getActorText(actor)[0].substr(13) : "null";
    }


}


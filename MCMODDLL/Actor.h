#pragma once

#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include "Spawn.h"
#include <vector>
#include <map>

using namespace SymHook;


/**
 * 从Actor 对象获取调式信息
 * @param actor Actor对象
 * @returnTRACEDESIGNTIME
 */
std::vector<std::string> getActorText(void *actor) {
    std::vector<std::string> info;
    if (!actor)return info;
    SYM_CALL(void(*)(void * , std::vector<std::string> &),
             MSSYM_MD5_f04fad6bac034f1e861181d3580320f2,
             actor, info);
    return info;
}


//0: Entity type: minecraft:villager_v2<>
/**
 * 从Actor对象中取到实体名称
 * @param actor actor 对象
 * @return
 */
std::string getActorName(void *actor) {
//#warning this func is hardcoded, it may need rewrite when update the gamw
    return actor ? getActorText(actor)[0].substr(13) : "null";
}


void sendMobInfo() {
    auto mobNum = getMobCount(spawner);
    char str[64];
    sprintf_s(str, "total mob count: %d", mobNum);
    gamePrintf(str);
}

//爆炸使能
THook(
        void,
        MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ,
        void * exp
) {
    if (enableExplosion) {
        original(exp);
    }
}


/*
 * 实体标定(攻击实体的时候返回实体消息)
 */
//THook(
//        void,
//        MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z,
//        void *p1,
//        void * p2
//) {
//    if (p1 && p2) {
//        if (getActorName(p2) == "minecraft:villager_v2<>") {
//            std::string infoText;
//            SYM_CALL(void(*)(void * villager, std::string &),
//                     MSSYM_B1QE14buildDebugInfoB1AE10VillagerV2B2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
//                     p2, infoText
//            );
//            printf("%s", infoText.c_str());
//            gamePrintf(infoText);
//        }
//    }
//}

/*
 * 从ActorIdentifier 中提取出实体名称
 */
std::string actorIDtoString(char *actorID) {
    auto str = reinterpret_cast<std::string *>(actorID + 32);
    return std::string(*str);
}

std::map<std::string, std::vector<Vec3>> mobCounterList;

//hook实体生成，这里是用来统计实体数量的钩子
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
    // printf("spawn %s at %f %f %f \n", actorIDtoString(actorId).c_str(), pos->x, pos->y, pos->z);
    if (mobSpawnCounterStart && pos) {
        //如果计时器在运行就统计生成的Mob种类
        auto mobName = actorIDtoString(actorId);
        Vec3 vec(pos->x, pos->y, pos->z);
        mobCounterList[mobName].emplace_back(vec);
    }
    original(sp, bs, actorId, actor, pos, a6, a7, a8);
}

//开始生物计数
void startSpawnCounter() {
    if (mobSpawnCounterStart) {
        error("it's already start some ticks before");
    } else {
        mobCounterList.clear(); //清空计数器
        mobTickCounter = 0;
        mobSpawnCounterStart = true;
        gamePrintf("counter start, type ./spawner end to end the counter");
    }
}

//结束生物计数器
void endSpawnerCounter() {
    if (!mobSpawnCounterStart) { //没开始直接提示
        error("this command can only be run after the counter start");
    } else {
        mobSpawnCounterStart = false;
        gamePrintf("counter end");
    }
}


//生成分析
void spawnAnalysis(std::string &type) {
    //如果是0,防止发出除以0异常
    if (mobTickCounter == 0) {
        warning("no data");
        return;
    }
    if (type == "null") {
        //如果没有指定生物种类，放出大概的数据
        std::map<std::string, size_t> mobList;
        std::map<int, int> heightMap;
        std::map<int, int> disMap;
        auto playerPos = getPos(player);
        size_t totalNum = 0;
        for (const auto &item:mobCounterList) {
            mobList[item.first] = item.second.size();
            totalNum += item.second.size();

            for (auto vec : item.second) {
                heightMap[(int) vec.y]++;
                disMap[(int) distance(vec, *playerPos)]++;
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
        //给定生物种类(暂时未开发)
        auto iter = mobCounterList.find(type);
        if (iter == mobCounterList.end()) {
            gamePrintf("no mob type named %s", type.c_str());
        } else {
            gamePrintf("function developing\n");
        }
    }
}


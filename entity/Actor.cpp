//
// Created by xhy on 2020/8/25.
//

#include "Actor.h"
#include "tools/MathTool.h"
#include "lib/mod.h"
#include "lib/pch.h"
#include "lib/SymHook.h"
#include "tools/MessageBuilder.h"
#include <map>
#include <string>
#include <block/Block.h>
#include "level/Biome.h"

using namespace SymHook;

std::map<std::string, std::vector<Vec3>> mobCounterList;//NOLINT



Vec3 *Actor::getPos() {
    return SYM_CALL(
            Vec3*(*)(void * ),
            MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ,
            this
    );
}

void Actor::getViewActor(Vec3 *vec3, float val) {
    SYM_CALL(
            Vec3*(*)(Actor * , Vec3 *, float),
            MSSYM_B1QE13getViewVectorB1AA5ActorB2AAA4QEBAB1QA6AVVec3B2AAA1MB1AA1Z,
            this, vec3, val
    );
}


std::string Actor::getNameTag() {
    return *SYM_CALL(std::string *(*)(Actor * ),
                     MSSYM_B1QE10getNameTagB1AA5ActorB2AAA8UEBAAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
                     this
    );
}

BlockSource *Actor::getBlockSource() {
    //from Player::tickWorld
    return *((struct BlockSource **) this + 100);
}

void Actor::setGameMode(int mode) {
    SYM_CALL(void(*)(Actor * , int),
             MSSYM_B1QE17setPlayerGameTypeB1AE12ServerPlayerB2AAE15UEAAXW4GameTypeB3AAAA1Z,
             this,
             mode
    );

}

void Actor::printInfo() {
    MessageBuilder builder;
    auto position = this->getPos()->toBlockPos();
    auto chunkPos = position.toChunkPos();
    auto inChunkOffset = position.InChunkOffset();
    auto inSlimeChunk = chunkPos.isSlimeChunk();
    Vec3 viewVec{};
    this->getViewActor(&viewVec, 1);
    builder.pos(position);
    if (inSlimeChunk) {
        builder.sText(chunkPos.toString(), COLOR::GREEN);
    } else {
        builder.sText(chunkPos.toString(), COLOR::WHITE);
    }
    builder.text(" ")
            .text(inChunkOffset.toString())
            .text("\n")
            .vec3(viewVec)
            .text("\n d:")
            .num(this->getDimensionID());

    auto biome = this->getBlockSource()->getBiome(&position);
    auto name = biome->getBiomeName();
    builder.text(biome->getBiomeName())
            .text(" ").num(biome->getBiomeType()).send(this);
}

int Actor::getDimensionID() {
    return *(reinterpret_cast<int *>(this) + 51);
}


std::string ActorDefinitionIdentifier::getName() {
    auto str = reinterpret_cast<std::string *>((char *) this + 32);
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


//void sendMobInfo() {
//    int mobNum = getMobCount(globalSpawner);
//    char str[64];
//    // info("total mob count: %d", mobNum);
//}
//
//void startSpawnCounter() {
//    if (mobSpawnCounterStart) {
//        //error("it's already start some ticks before");
//    } else {
//        mobCounterList.clear();
//        mobTickCounter = 0;
//        mobSpawnCounterStart = true;
//        // info("counter start, type ./spawner end to end the counter");
//    }
//}
//
//void endSpawnerCounter() {
//    if (!mobSpawnCounterStart) {
//        //  error("this command can only be run after the counter start");
//    } else {
//        mobSpawnCounterStart = false;
//        //  info("counter end");
//    }
//}

//void spawnAnalysis(std::string &type) {
////    if (mobTickCounter == 0) {
////        //todo: write
////        // warning("no data");
////        return;
////    }
////    if (type == "null") {
////        //todo mob count
////        std::map<std::string, size_t> mobList;
////        std::map<int, int> heightMap;
////        std::map<int, int> disMap;
////        auto playerPos = getPos(globalPlayer);
////        size_t totalNum = 0;
////        for (const auto &item:mobCounterList) {
////            mobList[item.first] = item.second.size();
////            totalNum += item.second.size();
////
////            for (auto vec : item.second) {
////                heightMap[(int) vec.y]++;
////                disMap[(int) math::distance(vec, *playerPos)]++;
////            }
////        }
////        sendBroadcastMessage("total §2%d §r tick", mobTickCounter);
////        for (auto &i: mobList)
////            sendBroadcastMessage("%s : §2%d       §r(§2%.2f§r/h)\n", i.first.c_str(), i.second,
////                                 (float) i.second * 72000.0 / (float) mobTickCounter);
////        sendBroadcastMessage("-------distance map---------");
////        for (auto &i: heightMap)
////            sendBroadcastMessage("[%d-%d]: §2%d", i.first, i.first + 1, i.second);
////        sendBroadcastMessage("--------height map--------");
////        for (auto &i: heightMap)
////            sendBroadcastMessage("%d: §2%d", i.first, i.second);
//
//    } else {
//
//        auto iter = mobCounterList.find(type);
//        if (iter == mobCounterList.end()) {
//            //   info("no mob type named %s", type.c_str());
//        } else {
//            //  info("function developing\n");
//        }
//    }
//}

std::string getActorName(void *actor) {
    return actor ? getActorText(actor)[0].substr(13) : "null";
}

//攻击实体
//THook(
//        void,
//        MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z,
//        void *p1,
//        void * p2
//) {
//    if (p1 && p2) {
//        // if (getActorName(p2) == "minecraft:villager_v2<>") {
//        original(p1, p2);
//        if (p2) {
//            std::string infoText;
//            //获取实体信息并设置命名牌
//            SYM_CALL(void(*)(void * mob, std::string &),
//                     MSSYM_B1QE14buildDebugInfoB1AA3MobB2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
//                     p2, infoText
//            );
//
//            SYM_CALL(
//                    void(*)(void * actor,
//                    const std::string &str),
//                    MSSYM_B1QE10setNameTagB1AA5ActorB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
//                    p2,
//                    infoText
//            );
//        }
//    }
//}
//spawn mob
THook(
        void,
        MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z,
        void *sp,
        void *bs,
        ActorDefinitionIdentifier *actorId,
        void *actor,
        Vec3 *pos,
        bool a6,
        bool a7,
        bool a8
) {
    //printf("(%f, %f, %f)\n", pos->x, pos->y, pos->z);
//    if (mobSpawnCounterStart && pos) {
//        auto mobName = actorId->getName();
//        Vec3 vec(pos->x, pos->y, pos->z);
//        mobCounterList[mobName].emplace_back(vec);
//    }
    original(sp, bs, actorId, actor, pos, a6, a7, a8);
}


//THook(
//        void,
//        MSSYM_MD5_4ad35b002b3931f6af40cb4fe59053ef,
//        void *self,
//        void *actorID,
//        void *actor,
//        Vec3 *pos,
//        int flag
//) {
//    // printf("   constructor (%f, %f, %f)\n", pos->x, pos->y, pos->z);
//    original(self, actorID, actor, pos, flag);
//}


//set actor pos
THook(
        void,
        MSSYM_B1QA6setPosB1AA5ActorB2AAE13UEAAXAEBVVec3B3AAAA1Z,
        void *self,
        Vec3 * pos
) {
//    if(self != globalPlayer){
//        printf("set pos: (%f, %f, %f)\n", pos->x, pos->y, pos->z);
//    }
    original(self, pos);
}


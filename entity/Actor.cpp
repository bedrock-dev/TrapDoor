//
// Created by xhy on 2020/8/25.
//

#include "Actor.h"
#include "tools/MathTool.h"
#include "lib/mod.h"
#include "lib/pch.h"
#include "lib/SymHook.h"
#include "lib/version.h"
#include "tools/MsgBuilder.h"
#include <map>
#include "tools/Message.h"
#include <string>
#include <block/Block.h>
#include "level/Biome.h"
#include "level/Level.h"
#include "common/Trapdoor.h"
#include <bitset>

using namespace SymHook;


std::map<std::string, std::vector<Vec3>> mobCounterList;//NOLINT

uint64_t NetworkIdentifier::getHash() {
    return SYM_CALL(
            uint64_t(*)(NetworkIdentifier * ),
            MSSYM_B1QA7getHashB1AE17NetworkIdentifierB2AAA4QEBAB1UA3KXZ,
            this
    );
}


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
    auto position = this->getPos();
    auto playerBlockPos = position->toBlockPos();
    auto chunkPos = playerBlockPos.toChunkPos();
    auto inChunkOffset = playerBlockPos.InChunkOffset();
    auto inSlimeChunk = chunkPos.isSlimeChunk();
    Vec3 viewVec{};
    this->getViewActor(&viewVec, 1);
    auto biome = this->getBlockSource()->getBiome(&playerBlockPos);
    auto name = biome->getBiomeName();

    std::string MinecraftVersion = stringFmt("Minecraft Bedrock(BDS) %s  (%s)\n\n", minecraftVersion,
                                             trapDoorVersion);
    std::string xyz = stringFmt("XYZ: %.2f / %.2f / %.2f\n", position->x, position->y, position->z);
    std::string block = stringFmt("Block: %d %d %d\n", playerBlockPos.x, playerBlockPos.y, playerBlockPos.z);
    std::string chunk = "Chunk: " + inChunkOffset.toString() + " in " + chunkPos.toString() + "\n";
    std::string facing = "Facing: " + viewVec.toDirString();
    facing += stringFmt("(%.2f / %.2f / %.2f)\n", viewVec.x, viewVec.y, viewVec.z);
    std::string biomeString = stringFmt("Biome: minecraft:%s (%d)\n", name.c_str(), biome->getBiomeType());
    std::string dimString = stringFmt("Dimension: %s (%d)\n", this->getDimensionName().c_str(), this->getDimensionID());

    builder.text(MinecraftVersion)
            .text(xyz)
            .text(block);
    if (inSlimeChunk) {
        builder.sText(chunk, COLOR::GREEN);
    } else {
        builder.text(chunk);
    }
    builder.text(facing).text(biomeString).text(dimString)
            .send(this);
}


int Actor::getDimensionID() {

    return *(reinterpret_cast<int *>(this) + 51);
}

Dimension *Actor::getDimension() {
    return globalLevel->getDimFromID(this->getDimensionID());
}

std::string Actor::getDimensionName() {
    auto id = this->getDimensionID();
    if (id == 0)return "Overworld";
    if (id == 1)return "Nether";
    if (id == 2)return "The end";
    return "Unknown";
}

NetworkIdentifier *Actor::getClientID() {
    //  ServerPlayer::isHostingPlayer
    return reinterpret_cast<NetworkIdentifier *>((char *) this + 2432);
}

CMD_LEVEL Actor::getCommandLevel() {
    return SYM_CALL(
            CMD_LEVEL(*)(Actor * ),
            MSSYM_B1QE25getCommandPermissionLevelB1AA6PlayerB2AAA4UEBAB1QE25AW4CommandPermissionLevelB2AAA2XZ,
            this
    );
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
//THook(
//        bool,
//        MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z,
//        void *sp,
//        void *bs,
//        ActorDefinitionIdentifier *actorId,
//        void *actor,
//        Vec3 *pos,
//        bool a6,
//        bool a7,
//        bool a8
//) {
//   // printf("(%f, %f, %f) ==> %s\n", pos->x, pos->y, pos->z, actorId->getName().c_str());
////    if (mobSpawnCounterStart && pos) {
////        auto mobName = actorId->getName();
////        Vec3 vec(pos->x, pos->y, pos->z);
////        mobCounterList[mobName].emplace_back(vec);
////    }
//    return original(sp, bs, actorId, actor, pos, a6, a7, a8);
//    //  return false;
//}



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
//THook(
//        void,
//        MSSYM_B1QA6setPosB1AA5ActorB2AAE13UEAAXAEBVVec3B3AAAA1Z,
//        void *self,
//        Vec3 * pos
//) {
////    if(self != globalPlayer){
////        printf("set pos: (%f, %f, %f)\n", pos->x, pos->y, pos->z);
////    }
//    original(self, pos);
//}


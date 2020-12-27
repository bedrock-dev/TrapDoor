//
// Created by xhy on 2020/8/25.
//

#include <bitset>
#include <map>

#include "Actor.h"
#include "lib/mod.h"
#include "lib/version.h"
#include "tools/MsgBuilder.h"
#include "tools/Message.h"
#include "block/Block.h"
#include "world/Biome.h"
#include "PlayerInventory.h"
#include "block/BlockSource.h"


namespace trapdoor {

    using namespace SymHook;

    uint64_t NetworkIdentifier::getHash() {
        return SYM_CALL(
                uint64_t(*)(NetworkIdentifier * ),
                SymHook::MSSYM_B1QA7getHashB1AE17NetworkIdentifierB2AAA4QEBAB1UA3KXZ,
                this
        );
    }


    Vec3 *Actor::getPos() {
        return SYM_CALL(
                Vec3 * (*)(void * ),
                SymHook::MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ,
                this
        );
    }

    void Actor::getViewActor(Vec3 *vec3, float val) {
        SYM_CALL(
                Vec3 * (*)(Actor * , Vec3 *, float),
                SymHook::MSSYM_B1QE13getViewVectorB1AA5ActorB2AAA4QEBAB1QA6AVVec3B2AAA1MB1AA1Z,
                this, vec3, val
        );
    }


    std::string Actor::getNameTag() {
        return *SYM_CALL(std::string * (*)(Actor * ),
                         SymHook::MSSYM_B1QE10getNameTagB1AA5ActorB2AAA8UEBAAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
                         this
        );
    }

    BlockSource *Actor::getBlockSource() {
        //from Player::tickWorld
        return *((struct BlockSource **) this + 100);
    }

    void Actor::setGameMode(int mode) {
        SYM_CALL(void(*)(Actor * , int),
                 SymHook::MSSYM_B1QE17setPlayerGameTypeB1AE12ServerPlayerB2AAE15UEAAXW4GameTypeB3AAAA1Z,
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

        std::string MinecraftVersion = format("Minecraft Bedrock(BDS) %s  (%s)\n\n", minecraftVersion,
                                              trapDoorVersion);
        std::string xyz = format("XYZ: %.2f / %.2f / %.2f\n", position->x, position->y, position->z);
        std::string block = format("Block: %d %d %d\n", playerBlockPos.x, playerBlockPos.y, playerBlockPos.z);
        std::string chunk = "Chunk: " + inChunkOffset.toString() + " in " + chunkPos.toString() + "\n";
        std::string facing = "Facing: " + viewVec.toDirString();
        facing += format("(%.2f / %.2f / %.2f)\n", viewVec.x, viewVec.y, viewVec.z);
        std::string biomeString = format("Biome: minecraft:%s (%d)\n", name.c_str(), biome->getBiomeType());
        std::string dimString = format("Dimension: %s (%d)\n", this->getDimensionName().c_str(),
                                       this->getDimensionID());

        builder.text(MinecraftVersion)
                .text(xyz)
                .text(block);
        if (inSlimeChunk) {
            builder.sText(chunk, MSG_COLOR::GREEN);
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
        return this->getLevel()->getDimFromID(this->getDimensionID());
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
                SymHook::MSSYM_B1QE25getCommandPermissionLevelB1AA6PlayerB2AAA4UEBAB1QE25AW4CommandPermissionLevelB2AAA2XZ,
                this
        );
    }

    PlayerInventory *Actor::getPlayerInventory() {
        return SYM_CALL(
                PlayerInventory * (*)(Actor * ),
                SymHook::MSSYM_B1QE11getSuppliesB1AA6PlayerB2AAE23QEAAAEAVPlayerInventoryB2AAA2XZ,
                this
        );
    }

    unsigned int Actor::getSelectSlot() {
        return *(unsigned int *) reinterpret_cast<char *>(this + 168);
    }

    Level *Actor::getLevel() {
        return bdsMod->getLevel();
    }


    std::string ActorDefinitionIdentifier::getName() {
        auto str = reinterpret_cast<std::string *>((char *) this + 32);
        return std::string(*str);
    }

    std::vector<std::string> getActorText(void *actor) {
        std::vector<std::string> info;
        if (!actor)return info;
        SYM_CALL(void(*)(void * , std::vector<std::string> &),
                 SymHook::MSSYM_MD5_f04fad6bac034f1e861181d3580320f2,
                 actor, info);
        return info;
    }


    std::string getActorName(void *actor) {
        return actor ? getActorText(actor)[0].substr(13) : "null";
    }
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


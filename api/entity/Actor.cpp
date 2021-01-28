//
// Created by xhy on 2020/8/25.
//

#include <bitset>
#include <map>

#include "Actor.h"
#include "lib/mod.h"
#include "tools/MsgBuilder.h"
#include "tools/Message.h"
#include "block/Block.h"
#include "world/Biome.h"
#include "PlayerInventory.h"
#include "block/BlockSource.h"
#include "Dimension.h"
#include "tools/DirtyLogger.h"
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
        //!from Player::tickWorld
        return *((struct BlockSource **) this + 100);
    }

    void Actor::setGameMode(int mode) {
        SYM_CALL(void(*)(Actor * , int),
                 SymHook::MSSYM_B1QE17setPlayerGameTypeB1AE12ServerPlayerB2AAE15UEAAXW4GameTypeB3AAAA1Z,
                 this,
                 mode
        );
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

    PlayerPermissionLevel Actor::getCommandLevel() {
        return SYM_CALL(
                PlayerPermissionLevel(*)(Actor * ),
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
        //!这个api是有问题的
        return 0;
        //  return *(unsigned int *) reinterpret_cast<char *>(this + 168);
    }

    Level *Actor::getLevel() {
        return bdsMod->getLevel();
    }

    std::string Actor::getActorId() {
        std::vector<std::string> info;
        SYM_CALL(void(*)(void * , std::vector<std::string> &),
                 SymHook::MSSYM_MD5_f04fad6bac034f1e861181d3580320f2,
                 this, info);
        if (info.empty())return "null";
        std::string name = info[0];
        name.erase(0, 23); //remove:Entity:minecraft
        name.pop_back();
        name.pop_back(); //remove <>
        return name;
    }

    BlockPos Actor::getStandPosition() {
        auto headPos = this->getPos()->toBlockPos();
        return {headPos.x, headPos.y - 2, headPos.z};
    }

    void Actor::setNameTag(const std::string &name) {
        SYM_CALL(
                void(*)(void * actor,
                const std::string &str),
                MSSYM_B1QE10setNameTagB1AA5ActorB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z,
                this,
                name
        );
    }

    std::string ActorDefinitionIdentifier::getName() {
        auto str = reinterpret_cast<std::string *>((char *) this + 32);
        return std::string(*str);
    }

}


using namespace SymHook;

THook(
        void,
        MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z,
        trapdoor::Actor *p1,
        trapdoor::Actor * p2
) {
    if (p2) {
        auto result = trapdoor::bdsMod->attackEntityHook(p1, p2);
        if (result) {
            original(p1, p2);
        }
    } else {
        original(p1, p2);
    }
}
//spawn mob



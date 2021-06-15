//
// Created by xhy on 2020/8/25.
//
// 
// 
//
#include <bitset>
#include "Actor.h"
#include "tools/MsgBuilder.h"
#include "world/Biome.h"
#include "block/BlockSource.h"
#include "Dimension.h"
#include "tools/CastHelper.h"
#include "Offset.h"
#include "lib/Loader.h"

namespace trapdoor {


    uint64_t NetworkIdentifier::getHash() {
        return SymCall("?getHash@NetworkIdentifier@@QEBA_KXZ", uint64_t, NetworkIdentifier*)(this);
    }


    Vec3 *Actor::getPos() {
        return SymCall("?getPos@Actor@@UEBAAEBVVec3@@XZ", Vec3*, Actor*)(this);

    }

    void Actor::getViewActor(Vec3 *vec3, float val) {
        SymCall("?getViewVector@Actor@@QEBA?AVVec3@@M@Z", Vec3*, Actor*, Vec3*, float)(this, vec3, val);
    }


    std::string Actor::getNameTag() {
        return SymCall("?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", std::string&, Actor*)(this);
    }

    BlockSource *Actor::getBlockSource() {
        //!from Player::tickWorld
        //  return offset_cast<BlockSource *>(this, 100);
        return *((struct BlockSource **) this + off::PLAYER_GET_BLOCKSOURCE);
    }

    void Actor::setGameMode(int mode) {
        SymCall("?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z", void, Actor*, int)(this, mode);

    }

    int Actor::getDimensionID() {
        return *offset_cast<int *>(this, off::ACTOR_GET_DIMENSION_ID);
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
        //! from  ServerPlayer::isHostingPlayer
        return offset_cast<NetworkIdentifier *>(this, off::ACTOR_GET_CLIENT_ID);
    }

    PlayerPermissionLevel Actor::getCommandLevel() {
        return SymCall("?getCommandPermissionLevel@Player@@UEBA?AW4CommandPermissionLevel@@XZ", PlayerPermissionLevel, Actor*)(this);

    }

    PlayerInventory *Actor::getPlayerInventory() {
        return SymCall("?getSupplies@Player@@QEAAAEAVPlayerInventory@@XZ", PlayerInventory*, Actor*)(this);

    }


    //from: Actor::getLevel
    Level *Actor::getLevel() { //NOLINT
        return bdsMod->getLevel();
        // return *reinterpret_cast<trapdoor::Level **>((VA) this + 816);
    }

    std::string Actor::getActorId() {
        std::vector<std::string> info;
        SymCall("?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@"
            "2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z",
            void, void*, std::vector<std::string> &)(this,info);

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
        SymCall("?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@"
            "@V?$allocator@D@2@@std@@@Z", void, Actor*, const std::string)(this, name);

    }

    std::string ActorDefinitionIdentifier::getName() {
        auto str = offset_cast<std::string *>(this, off::ACTOR_ID_GET_NAME);
        return std::string(*str);
    }

}


THook(void,"?attack@Player@@UEAA_NAEAVActor@@@Z",
        trapdoor::Actor *p1, trapdoor::Actor * p2) {
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



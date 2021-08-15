//
// Created by xhy on 2020/8/25.
//

#include "Actor.h"

#include <bitset>

#include "Dimension.h"
#include "Offset.h"
#include "block/BlockSource.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/CastHelper.h"
#include "tools/MsgBuilder.h"
#include "world/Biome.h"

namespace trapdoor {

    using namespace SymHook;

    uint64_t NetworkIdentifier::getHash() {
        return SYM_CALL(uint64_t(*)(NetworkIdentifier *),
                        SymHook::NetworkIdentifier_getHash_d932dec8, this);
    }

    Vec3 *Actor::getPos() {
        return SYM_CALL(Vec3 * (*)(void *), SymHook::Actor_getPos_cecb628b,
                        this);
    }

    void Actor::getViewActor(Vec3 *vec3, float val) {
        SYM_CALL(Vec3 * (*)(Actor *, Vec3 *, float),
                 SymHook::Actor_getViewVector_01c92121, this, vec3, val);
    }

    std::string Actor::getNameTag() {
        return *SYM_CALL(std::string * (*)(Actor *),
                         SymHook::Actor_getNameTag_7044ab83, this);
    }

    BlockSource *Actor::getBlockSource() {
        //! from Player::tickWorld
        //  return offset_cast<BlockSource *>(this, 100);
        return *((struct BlockSource **)this + off::PLAYER_GET_BLOCKSOURCE);
    }

    void Actor::setGameMode(int mode) {
        SYM_CALL(void (*)(Actor *, int),
                 SymHook::ServerPlayer_setPlayerGameType_058d8c73, this, mode);
    }

    int Actor::getDimensionID() {
        return *offset_cast<int *>(this, off::ACTOR_GET_DIMENSION_ID);
    }

    Dimension *Actor::getDimension() {
        return this->getLevel()->getDimFromID(this->getDimensionID());
    }

    std::string Actor::getDimensionName() {
        auto id = this->getDimensionID();
        if (id == 0) return "Overworld";
        if (id == 1) return "Nether";
        if (id == 2) return "The end";
        return "Unknown";
    }

    NetworkIdentifier *Actor::getClientID() {
        //! from  ServerPlayer::isHostingPlayer
        return offset_cast<NetworkIdentifier *>(this, off::ACTOR_GET_CLIENT_ID);
    }

    PlayerPermissionLevel Actor::getCommandLevel() {
        return SYM_CALL(PlayerPermissionLevel(*)(Actor *),
                        SymHook::Player_getCommandPermissionLevel_40b0e608,
                        this);
    }

    // from: Actor::getLevel
    Level *Actor::getLevel() {  // NOLINT
        return bdsMod->getLevel();
        // return *reinterpret_cast<trapdoor::Level **>((VA) this + 816);
    }

    std::string Actor::getActorId() {
        std::vector<std::string> info;
        SYM_CALL(void (*)(void *, std::vector<std::string> &),
                 SymHook::Actor_getDebugText_f04fad6b, this, info);
        if (info.empty()) return "null";
        std::string name = info[0];
        name.erase(0, 23);  // remove:Entity:minecraft
        return name.substr(0, name.size() - 2);
    }

    BlockPos Actor::getStandPosition() {
        auto headPos = this->getPos()->toBlockPos();
        return {headPos.x, headPos.y - 2, headPos.z};
    }

    void Actor::setNameTag(const std::string &name) {
        SYM_CALL(void (*)(void *actor, const std::string &str),
                 Actor_setNameTag_2f9772d3, this, name);
    }

    std::string ActorDefinitionIdentifier::getName() {
        auto str = offset_cast<std::string *>(this, off::ACTOR_ID_GET_NAME);
        return std::string(*str);
    }

}  // namespace trapdoor

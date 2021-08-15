#pragma once
#include <cstdint>
#include <utility>
namespace off {

    // BlockLegacy::getVariant(BlockLegacy *this, char *a2);
    constexpr uint64_t BLOCK_GET_VARIANT = 0x8;

    // BlockActor::tick
    constexpr uint64_t BLOCKACTOR_GET_POSITION = 0x2c;

    constexpr uint64_t BLOCK_GET_LEGACY = 0x10;

    // BlockLegacy::getBlockItemId(BlockLegacy *this)
    constexpr uint64_t BLOCKLEGACY_GET_BLOCK_ID = 0x14C;

    // TODO
    constexpr uint64_t BASECIRCUITCOMPONENT_GET_STRENGTH = 0x34;

    // todo
    constexpr std::pair<uint64_t, uint64_t> BASECIRCUITCOMPONENT_SOURCE_RANGE =
        {0x1, 0x2};

    // OK
    // CommandRequestPacket::createCommandContext(
    constexpr uint64_t COMMAND_PACKET_STR = 0x30;

    // OK
    // Player::tickWorld
    constexpr uint64_t PLAYER_GET_BLOCKSOURCE = 109;

    // OK
    // Actor::getDimensionId
    constexpr uint64_t ACTOR_GET_DIMENSION_ID = 0xEC;

    // OK
    // from  ServerPlayer::isHostingPlayer
    constexpr uint64_t ACTOR_GET_CLIENT_ID = 2712;

    // todo
    constexpr uint64_t ACTOR_ID_GET_NAME = 0x20;

    // todo
    constexpr uint64_t ITEM_GET_NUM = 0x22;

    constexpr uint64_t BIOME_GET_NAME = 0x8;

    constexpr uint64_t DIMENSION_GET_CIRCUIT_SYSTEM = 0x21;

    constexpr uint64_t CIRCUIT_GET_GRAPH = 0x8;

    constexpr uint64_t DIMENSION_IS_RS_TICK = 0x4B;
    // Spawner::_spawnMobCluster
    constexpr uint64_t MOB_SPAWN_DATA_GET_RULE = 184;

    constexpr std::pair<uint64_t, uint64_t> LEVEL_FOREACH_PLAYER = {0xE, 0xF};

    // MobSpawnData::MobSpawnData
    constexpr uint64_t MOB_SPAWN_DATA_GET_ACTOR_ID = 0x8;

};  // namespace off
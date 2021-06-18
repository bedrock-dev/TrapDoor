//
// Created by xhy on 2020/12/31.
//

#include "SpawnHelper.h"
#include "graphics/Particle.h"
#include "graphics/Graphics.h"
#include "graphics/AABB.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "tools/DirtyLogger.h"
#include "block/BlockLegacy.h"
#include "block/Block.h"
#include "BlockSource.h"
#include "Message.h"
#include "MsgBuilder.h"
#include "Offset.h"

namespace mod {


    namespace {
    }

    void SpawnHelper::tick() {
        if (!this->enable)return;
        if (gameTick % 40 == 0) {
            this->draw();
        }
        this->gameTick = (this->gameTick + 1) % 80;
    }

    void SpawnHelper::draw() {
        if (!this->enable)return;
        if (!verticalSpawnPositions.empty()) {
            trapdoor::BoundingBox boundingBox{verticalSpawnPositions[0], verticalSpawnPositions[0]};
            trapdoor::spawnRectangleParticle(boundingBox.toAABB(), trapdoor::GRAPHIC_COLOR::GREEN, dimensionID);
        }
        for (auto i = 1; i < verticalSpawnPositions.size(); i++) {
            trapdoor::BoundingBox boundingBox{verticalSpawnPositions[i], verticalSpawnPositions[i]};
            trapdoor::spawnRectangleParticle(boundingBox.toAABB(), trapdoor::GRAPHIC_COLOR::RED, dimensionID);
        }
    }

    void SpawnHelper::updateVerticalSpawnPositions(const trapdoor::BlockPos &pos, trapdoor::Actor *player) {
        if (!this->enable)return;
        this->verticalSpawnPositions.clear();
        auto dim = player->getDimensionID();
        this->dimensionID = dim;
        int maxY = dim != 1 ? 255 : 127;
        trapdoor::BlockPos topPos = {pos.x, maxY, pos.z};
        do {
            findNextSpawnPosition(player->getBlockSource(), &topPos, 41);
            //   L_INFO("find pos %d %d %d", topPos.x, topPos.y, topPos.z);
            if (topPos.y > 0)
                this->verticalSpawnPositions.emplace_back(topPos.x, topPos.y, topPos.z);
        } while (topPos.y > 0);
    }


    void
    SpawnHelper::printSpawnProbability(trapdoor::Actor *player, const trapdoor::BlockPos &pos, uint32_t bright) const {
        if (!this->enable)return;
        auto dim = player->getDimensionID();
        int maxY = dim != 1 ? 255 : 127;
        trapdoor::BlockPos topPos = {pos.x, maxY, pos.z};
        bool isSurface = true;
        bool hasFound = false;
        while (topPos.y > 0) {
            findNextSpawnPosition(player->getBlockSource(), &topPos, 41);
            if (topPos.y == pos.y) {
                // L_INFO("pos %d %d %d  is valid spawn position surface: %d", pos.x, pos.y, pos.z, isSurface);
                hasFound = true;
                break;
            }
            isSurface = false;
        }
        if (!hasFound) {
            trapdoor::warning(player, "pos [%d %d %d]  is not valid spawn position ", pos.x, pos.y, pos.z);
            return;
        }

        SpawnConditions conditions{
                isSurface,
                false,
                false,
                !isSurface,
                0, 0, bright,
                pos
        };
        auto *bs = player->getBlockSource();
        auto *block = bs->getBlock(pos);
        std::map<std::string, int> spawnMap;
        for (int i = 0; i < 200; ++i) {
            auto mobData = getMobToSpawn(block->getLegacy(), conditions, bs);
            if (mobData)
                spawnMap[mobData->getActorID()->getName()]++;
        }
        int totalCount = 0;
        for (const auto &mob:spawnMap)
            totalCount += mob.second;
        trapdoor::MessageBuilder builder;
        builder.sTextF(trapdoor::MSG_COLOR::BOLD | trapdoor::MSG_COLOR::WHITE, "-- [%d %d %d] ", pos.x, pos.y, pos.z);
        if (isSurface) {
            builder.sTextF(trapdoor::MSG_COLOR::GREEN | trapdoor::MSG_COLOR::BOLD, "surface");
        } else {
            builder.sTextF(trapdoor::MSG_COLOR::RED | trapdoor::MSG_COLOR::BOLD, "underground");
        }
        builder.text(" --\n");
        for (const auto &mob:spawnMap) {
            builder.text(mob.first).text("    ").num(mob.second * 100 / totalCount).text("%%%%\n");
        }
        builder.send(player);
    }


    void findNextSpawnPosition(trapdoor::BlockSource *source, trapdoor::BlockPos *pos, unsigned int material) {
        using namespace SymHook;
        SYM_CALL(
                void(*)(trapdoor::BlockSource * , trapdoor::BlockPos *, unsigned int),
                MSSYM_B1QE23findNextSpawnBlockUnderB1AA7SpawnerB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEAVBlockPosB2AAE14W4MaterialTypeB2AAE24W4SpawnBlockRequirementsB3AAAA1Z,
                source, pos, material
        );
    }

    MobSpawnData *
    getMobToSpawn(trapdoor::BlockLegacy *legacy, const SpawnConditions &spawnConditions,
                  trapdoor::BlockSource *blockSource) {
        using namespace SymHook;
        return SYM_CALL(
                MobSpawnData*(*)(trapdoor::BlockLegacy * ,const SpawnConditions&, trapdoor::BlockSource*source),
                MSSYM_B1QE13getMobToSpawnB1AE11BlockLegacyB2AAE22UEBAPEBVMobSpawnerDataB2AAE19AEBVSpawnConditionsB2AAE15AEAVBlockSourceB3AAAA1Z,
                legacy,
                spawnConditions,
                blockSource
        );
    }

    MobSpawnRules *MobSpawnData::getSpawnRules() {
        //! Spawner::_spawnMobCluster
        return reinterpret_cast<MobSpawnRules *>(reinterpret_cast<char *>(this) + off::MOB_SPAWN_DATA_GET_RULE);
    }

    trapdoor::ActorDefinitionIdentifier *MobSpawnData::getActorID() {
        //!MobSpawnData::MobSpawnData
        return reinterpret_cast<trapdoor::ActorDefinitionIdentifier *>(reinterpret_cast<char *>(this) +
                                                                       off::MOB_SPAWN_DATA_GET_ACTOR_ID);
    }
}



//
// Created by xhy on 2020/12/27.
//

#include "HsaManager.h"

#include <string>

#include "BDSMod.h"
#include "Particle.h"
#include "TrapdoorMod.h"
#include "block/BlockSource.h"
#include "entity/Actor.h"
#include "graphics/AABB.h"
#include "graphics/Particle.h"
#include "lib/Remotery.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "world/Biome.h"
#include "world/Level.h"

namespace mod {

    bool HsaInfo::operator<(const mod::HsaInfo &rhs) const {
        return boundingBox < rhs.boundingBox;
    }

    trapdoor::BlockPos HsaManager::findB(trapdoor::Actor *player) {
        trapdoor::BoundingBox hsaBoundingBox;
        auto firsthsa = *((this->hsaList).begin());
        hsaBoundingBox.minPos = firsthsa.boundingBox.minPos;
        hsaBoundingBox.maxPos = firsthsa.boundingBox.maxPos;
        for (const auto &hsa : this->hsaList) {
            hsaBoundingBox.minPos.x =
                min(hsaBoundingBox.minPos.x, hsa.boundingBox.minPos.x);
            hsaBoundingBox.minPos.y =
                min(hsaBoundingBox.minPos.y, hsa.boundingBox.minPos.y);
            hsaBoundingBox.minPos.z =
                min(hsaBoundingBox.minPos.z, hsa.boundingBox.minPos.z);
            hsaBoundingBox.maxPos.x =
                max(hsaBoundingBox.maxPos.x, hsa.boundingBox.maxPos.x);
            hsaBoundingBox.maxPos.y =
                max(hsaBoundingBox.maxPos.y, hsa.boundingBox.maxPos.y);
            hsaBoundingBox.maxPos.z =
                max(hsaBoundingBox.maxPos.z, hsa.boundingBox.maxPos.z);
        }
        info(player, "%s  %s", hsaBoundingBox.minPos.toString().c_str(),
             hsaBoundingBox.maxPos.toString().c_str());
        info(player, "%d", firsthsa.dimensionID);
        int points = 0, maxPoints = 0;
        trapdoor::BlockPos pos;
        for (int x = hsaBoundingBox.minPos.x - 44;
             x <= hsaBoundingBox.maxPos.x + 44; x++)
            for (int y = max(hsaBoundingBox.minPos.y - 44, 0);
                 y <= min(hsaBoundingBox.maxPos.y + 44,
                          127 + firsthsa.dimensionID == 1 ? 0 : 128);
                 y++)
                for (int z = hsaBoundingBox.minPos.z - 44;
                     z <= hsaBoundingBox.maxPos.z + 44; z++) {
                    points = 0;
                    for (const auto &hsa : this->hsaList) {
                        float dis = hsa.boundingBox.getSpawnArea()
                                        .getCenter()
                                        .distanceTo({x, y, z});
                        if (dis >= 24.0 && dis <= 44.0) {
                            points += 1;
                        }
                    }
                    if (points > maxPoints) {
                        maxPoints = points;
                        pos = trapdoor::BlockPos(x, y, z);
                    }
                }
        broadcastMsg("N = %d", maxPoints);
        return pos;
    }

    void HsaManager::draw(trapdoor::Actor *player) {
        auto mod = bdsMod->asInstance<mod::TrapdoorMod>();
        if (!mod->getSimpleBuilder().isAble()) {
            trapdoor::info(player, "builder未开启");
            return;
        }
        trapdoor::BlockPos standPos = player->getStandPosition();
        auto block = player->getBlockSource()->getBlock(standPos.x, standPos.y,
                                                        standPos.z);
        for (const auto &hsa : this->hsaList) {
            trapdoor::BlockPos pos =
                hsa.boundingBox.getSpawnArea().getCenter().toBlockPos();
            player->getBlockSource()->setBlock(&pos, block);
        }
    }

    void HsaManager::tick() {
        rmt_ScopedCPUSample(HSA_TICK, 0);
        if (!this->enable) return;
        if (gameTick % 40 == 0) {
            trapdoor::GRAPHIC_COLOR color = trapdoor::GRAPHIC_COLOR::WHITE;
            for (const auto &hsa : this->hsaList) {
                switch (hsa.type) {
                    case PillagerOutpost:
                        color = trapdoor::GRAPHIC_COLOR::BLUE;
                        break;
                    case SwampHut:
                        color = trapdoor::GRAPHIC_COLOR::RED;
                        break;
                    case NetherFortress:
                        color = trapdoor::GRAPHIC_COLOR::GREEN;
                        break;
                    case OceanMonument:
                        color = trapdoor::GRAPHIC_COLOR::YELLOW;
                        break;
                    default:
                        break;
                }
                trapdoor::spawnRectangleParticle(hsa.boundingBox.getSpawnArea(),
                                                 color, true, hsa.dimensionID);
            }
        }
        this->gameTick = (this->gameTick + 1) % 80;
    }

    bool HsaManager::findHsa(const HsaInfo &hsaInfo) {
        return this->hsaList.find(hsaInfo) != this->hsaList.end();
    }

    void HsaManager::list(Actor *player) {
        // todo
        info(player, "developing");
    }

    void HsaManager::registerCommand(trapdoor::CommandManager &commandManager) {
        commandManager.registerCmd("hsa", "command.hsa.desc")
            ->then(ARG("clear", "command.hsa.clear.desc", NONE,
                       {
                           auto num = this->clear();
                           broadcastMsg("一共 %d 个hsa区域被清空", num);
                       }))
            ->then(ARG("list", "command.hsa.list.desc", NONE,
                       { this->list(player); }))
            ->then(ARG("show", "command.hsa.show.desc", BOOL,
                       {
                           this->setAble(holder->getBool());
                           info(player, "设置HSA显示为 %d", holder->getBool());
                       }))
            ->then(ARG("find", "command.hsa.find.desc", NONE,
                       {
                           broadcastMsg("find %s",
                                        this->findB(player).toString().c_str());
                       }))
            ->then(ARG("draw", "command.hsa.draw.desc", NONE,
                       { this->draw(player); }));
    }

}  // namespace mod
using namespace SymHook;

// HSA collector
THook(void, Spawner_spawnStructureMob_98a1693e, void *spawner,
      trapdoor::BlockSource *blockSource, trapdoor::BlockPos *blockPos,
      trapdoor::BoundingBox *hsa, void *spawnConditions) {
    // todo add hsa here
    original(spawner, blockSource, blockPos, hsa, spawnConditions);
    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
    auto &hsaManager = modInstance->getHsaManager();
    mod::HsaInfo info;
    info.boundingBox = {hsa->minPos, hsa->maxPos};
    //已有了就不加入了//为了节省一下群系计算时间？
    if (hsaManager.findHsa(info)) return;

    auto biome = blockSource->getBiome(blockPos);
    auto type = biome->getBiomeType();
    if (type == 5 || type == 18) {
        info.type = mod::StructureType::NetherFortress;
        info.dimensionID = trapdoor::Nether;
    } else if (type == 10) {
        info.type = mod::StructureType::OceanMonument;
    } else if (type == 15) {
        info.type = mod::StructureType::SwampHut;
    } else {
        info.type = mod::StructureType::PillagerOutpost;
    }

    hsaManager.insert(info);
    blockSource->getBiome(blockPos);
    modInstance->getHsaManager().insert(info);
}
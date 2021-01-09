//
// Created by xhy on 2020/12/27.
//

#include "HsaManager.h"
#include "graphics/Particle.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "block/BlockSource.h"
#include "tools/MsgBuilder.h"
#include "tools/Message.h"
#include "graphics/AABB.h"
#include "TrapdoorMod.h"
#include "world/Biome.h"

namespace mod {

    bool HsaInfo::operator<(const mod::HsaInfo &rhs) const {
        return boundingBox < rhs.boundingBox;
    }

    void HsaManager::tick() {
        if (!this->enable)return;
        if (gameTick % 40 == 0) {
            // printf("sum =  %zu\n", gameTick);
            trapdoor::GRAPHIC_COLOR color = trapdoor::GRAPHIC_COLOR::WHITE;
            for (const auto &hsa: this->hsaList) {
                switch (hsa.type) {
                    case PillagerOutpost:
                        color = trapdoor::GRAPHIC_COLOR::YELLOW;
                        break;
                    case SwampHut:
                        color = trapdoor::GRAPHIC_COLOR::GREEN;
                        break;
                    case NetherFortress:
                        color = trapdoor::GRAPHIC_COLOR::RED;
                        break;
                    case OceanMonument:
                        color = trapdoor::GRAPHIC_COLOR::BLUE;
                        break;
                    default:
                        break;
                }
                trapdoor::spawnRectangleParticle(hsa.boundingBox.getSpawnArea(), color,
                                                 hsa.dimensionID);
            }
        }
        this->gameTick = (this->gameTick + 1) % 80;
    }

    bool HsaManager::findHsa(const HsaInfo &hsaInfo) {
        return this->hsaList.find(hsaInfo) != this->hsaList.end();
    }

    void HsaManager::list(Actor *player) {
        //todo
        info(player, "developing");
    }

}
using namespace SymHook;

//HSA collector
THook(
        void,
        MSSYM_B2QUE17spawnStructureMobB1AA7SpawnerB2AAE20AEAAXAEAVBlockSourceB2AAE12AEBVBlockPosB2AAE25AEBUHardcodedSpawningAreaB1AE10LevelChunkB2AAE19AEBVSpawnConditionsB3AAAA1Z,
        void *spawner,
        trapdoor::BlockSource *blockSource,
        trapdoor::BlockPos *blockPos,
        trapdoor::BoundingBox *hsa,
        void * spawnconditions
) {
    //todo add hsa here
    original(spawner, blockSource, blockPos, hsa, spawnconditions);
    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
    auto &hsaManager = modInstance->getHsaManager();
    if (!hsaManager.isAble())return;
    mod::HsaInfo info;
    info.boundingBox = {hsa->minPos, hsa->maxPos};
    //已有了就不加入了//为了节省一下群系计算时间？
    if (hsaManager.findHsa(info))return;

    auto biome = blockSource->getBiome(blockPos);
    auto type = biome->getBiomeType();
    if (type == 5 || type == 18) {
        info.type = mod::StructureType::NetherFortress;
        info.dimensionID = 1;
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
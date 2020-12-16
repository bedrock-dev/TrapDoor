//
// Created by xhy on 2020/8/25.
//

#include "Trapdoor.h"
#include <map>
#include "RightClickManager.h"
#include "block/Block.h"
#include "commands/CommandManager.h"
#include "entity/PlayerBuffer.h"
#include "graphics/AABB.h"
#include "graphics/BlockPos.h"
#include "graphics/Graphics.h"
#include "graphics/Particle.h"
#include "graphics/Vec3.h"
#include "level/Biome.h"
#include "level/Level.h"

void *globalSpawner = nullptr;           //全局刷怪器对象
void *globalVillageManager = nullptr;  //全局村庄管理器对象
void *globalCommandRegistry = nullptr;
// CircuitSceneGraph *globalCircuitSceneGraph = nullptr;
void *globalCircuitSystem = nullptr;
Level *globalLevel = nullptr;

//粒子效果配置(性能配置)
int particleViewDistance = 1024;
uint64_t playerRand = 0;
bool enableMarkPos = false;
bool enableVillageShow = false;
bool enableBlockUpdate = true;
bool enableExtraTickWork = true;
bool enableExplosion = false;
bool mobSpawnCounterStart = false;
bool enableHopperCounter = false;
bool enableHsaShow = false;
int mobTickCounter = 0;
int hopperTickLength = 50;

CommandManager &getCommandManager() {
    static CommandManager commandManager;
    return commandManager;
}

std::map<std::string, PlayerBuffer> &getPlayerBuffer() {
    static std::map<std::string, PlayerBuffer> playerBuffer;
    return playerBuffer;
}

RightClickManager &getRightClickManager() {
    static RightClickManager rightClickManager;
    return rightClickManager;
}

void initRightClickManager() {
    //    auto &manager = getRightClickManager();
    //    manager.registerRightClickBackEvent("Cactus",
    //                                        RIGHT_CLICK_EVENT({
    //                                                              printf("%s
    //                                                              %d %d %d %f
    //                                                              %f %f\n",
    //                                                                     player->getNameTag().c_str(),
    //                                                                     pos.x,
    //                                                                     pos.y,
    //                                                                     pos.z,
    //                                                                     offset.x,
    //                                                                     offset.y,
    //                                                                     offset.z);
    //                                                          }));
}

std::set<BoundingBox> &getHardcodedSpawnAreas() {
    static std::set<BoundingBox> hsaList;
    return hsaList;
}

int showHsaFreq = 0;

void showHsa() {
    if (!enableHsaShow)
        return;
    showHsaFreq++;
    if (showHsaFreq == 39) {
        auto &hsaList = getHardcodedSpawnAreas();
        // printf("total %llu\n", num);
        auto num = hsaList.size();
        for (const auto &hsa : hsaList) {
            auto area = hsa.getSpwawnArea();
//			auto blockPos = area.p1.toBlockPos();
//			auto nearestPlayer = globalLevel->getNearestPlayer(blockPos);
//			if (!nearestPlayer) {
//			    L_DEBUG("can not find player");
//				return;
//			}
//			auto blockSource = nearestPlayer->getBlockSource();
//			auto biome = blockSource->getBiome(&(blockPos));
//			auto biomeType = biome->getBiomeType();
//			if (biomeType == 5 || biomeType == 18)
//				spawnRectangleParticleColor(area, graphics::COLOR::RED);
//			else if (biomeType == 10)
//				spawnRectangleParticleColor(area, graphics::COLOR::BLUE);
//			else if (biomeType == 15)
//				spawnRectangleParticleColor(area, graphics::COLOR::GREEN);
//			else
            spawnRectangleParticleColor(area, graphics::COLOR::YELLOW);
        }
        showHsaFreq = 0;
    }
}

namespace trapdoor {
    Level *TrapdoorMod::getLevel() {
        return this->globalLevel;
    }

    void TrapdoorMod::setLevel(Level *level) {
        this->globalLevel = level;
    }

}  // namespace trapdoor

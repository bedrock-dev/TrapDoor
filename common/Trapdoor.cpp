//
// Created by xhy on 2020/8/25.
//

#include "Trapdoor.h"
#include "level/Level.h"
#include "commands/CommandManager.h"
#include <map>
#include "RightClickManager.h"
#include "Vec3.h"
#include "BlockPos.h"
#include "entity/PlayerBuffer.h"

void *globalSpawner = nullptr; //全局刷怪器对象
void *globalVillageManager = nullptr; //全局村庄管理器对象
void *globalCommandRegistry = nullptr;
//CircuitSceneGraph *globalCircuitSceneGraph = nullptr;
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
//                                                              printf("%s %d %d %d %f %f %f\n",
//                                                                     player->getNameTag().c_str(),
//                                                                     pos.x, pos.y, pos.z, offset.x, offset.y,
//                                                                     offset.z);
//                                                          }));
}





//bool Trapdoor::initialize() {
//
//    return true;
//}

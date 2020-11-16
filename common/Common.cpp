//
// Created by xhy on 2020/8/25.
//

#include "Common.h"
#include "level/Level.h"

void *globalSpawner = nullptr; //全局刷怪器对象
void *globalVillageManager = nullptr; //全局村庄管理器对象
void *globalCommandRegistry = nullptr;
CircuitSceneGraph *globalCircuitSceneGraph = nullptr;
void *globalCircuitSystem = nullptr;
Level *globalLevel = nullptr;


//粒子效果配置(性能配置)
int particleViewDistance = 128;
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

std::set<PlayerSpace> &getPlayerSpace() {
    static std::set<PlayerSpace> playerSpaceList;
    return playerSpaceList;
}

CommandManager &getCommandManager() {
    static CommandManager commandManager;
    return commandManager;
}



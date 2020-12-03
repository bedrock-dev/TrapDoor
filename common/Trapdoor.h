//
// Created by xhy on 2020/8/25.
//

#ifndef TRAPDOOR_TRAPDOOR_H
#define TRAPDOOR_TRAPDOOR_H

#include <set>
#include <cstdio>
#include <map>
#include <string>
#include "commands/CommandManager.h"
#include "ConfigManager.h"

class Level;

class CircuitSceneGraph;

class Actor;

class PlayerBuffer;

//class Trapdoor {
//    Level *level = nullptr;
//    CommandManager *manager{};
//    ConfigManager *configManager{};
//public:
//    bool initialize();
//};

extern void *globalSpawner; //全局刷怪器对象
extern void *globalCommandRegistry;
extern void *globalVillageManager; //全局村庄管理器对象
//extern CircuitSceneGraph *globalCircuitSceneGraph;
extern void *globalCircuitSystem;
extern Level *globalLevel;

CommandManager &getCommandManager();

//粒子效果配置(性能配置)
extern int particleViewDistance;
extern bool enableMarkPos;
extern bool enableVillageShow;
extern bool enableExtraTickWork;
extern bool enableExplosion;
extern bool mobSpawnCounterStart;
extern bool enableBlockUpdate;
extern bool enableHopperCounter;
extern int mobTickCounter;
extern int hopperTickLength;


#endif //TRAPDOOR_TRAPDOOR_H

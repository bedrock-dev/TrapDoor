//
// Created by xhy on 2020/8/25.
//
/*
 * todo 1.把所有的全局变量塞到TrapdoorMod对象中，以后通过唯一的mod对象访问
 * todo 这大概要2021年再做了。咕咕咕
 *
 */
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

class BoundingBox;

class PlayerBuffer;

class RightClickManager;

extern void *globalSpawner; //全局刷怪器对象
extern void *globalCommandRegistry;
extern void *globalVillageManager; //全局村庄管理器对象
//extern CircuitSceneGraph *globalCircuitSceneGraph;
extern void *globalCircuitSystem;
extern Level *globalLevel;

CommandManager &getCommandManager();

std::map<std::string, PlayerBuffer> &getPlayerBuffer();

RightClickManager &getRightClickManager();

std::set<BoundingBox>& getHardcodedSpawnAreas();
//粒子效果配置(性能配置)
extern int particleViewDistance;
extern bool enableMarkPos;
extern bool enableVillageShow;
extern bool enableExtraTickWork;
extern bool enableExplosion;
extern bool mobSpawnCounterStart;
extern bool enableBlockUpdate;
extern bool enableHopperCounter;
extern bool enableHsaShow;
extern int mobTickCounter;
extern int hopperTickLength;

void initRightClickManager();

namespace trapdoor {
    class TrapdoorMod {
        //todo: put all the global variable here;
    private:
        Level *globalLevel;
    public:
        Level *getLevel();

        void setLevel(Level *level);
    };
}

//临时的函数

void  showHsa();


#endif //TRAPDOOR_TRAPDOOR_H

//
// Created by xhy on 2020/8/25.
//

#ifndef TRAPDOOR_COMMON_H
#define TRAPDOOR_COMMON_H

#include "block/Block.h"

extern void *globalPlayer; //全局玩家对象
extern void *globalLevel; //全局存档对象
extern void *globalDimension; //全局维度对象
extern BlockSource *globalBlockSource; //全局bs对象
extern void *globalSpawner; //全局刷怪器对象
extern void *globalVillageManager; //全局村庄管理器对象
extern CircuitSceneGraph *globalCircuitSceneGraph;
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

#endif //TRAPDOOR_COMMON_H

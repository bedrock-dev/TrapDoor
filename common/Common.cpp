//
// Created by xhy on 2020/8/25.
//
#include "Common.h"

void *globalPlayer = nullptr; //全局玩家对象
void *globalLevel = nullptr; //全局存档对象
void *globalDimension = nullptr; //全局维度对象
BlockSource *globalBlockSource = nullptr; //全局bs对象
void *globalSpawner = nullptr; //全局刷怪器对象
void *globalVillageManager = nullptr; //全局村庄管理器对象
CircuitSceneGraph *globalCircuitSceneGraph = nullptr;
//粒子效果配置(性能配置)
int particleViewDistance = 128;


bool enableMarkPos = false;
bool enableVillageShow = false;
bool enableBlockUpdate = true;
bool enableExtraTickWork = true;
bool enableExplosion = false;
bool mobSpawnCounterStart = false;
bool enableHopperCounter = false;
int mobTickCounter = 0;
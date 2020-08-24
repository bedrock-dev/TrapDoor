#pragma once

#include <vector>
#include "lib/pch.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include <string>
#include <ostream>
#include "Vec3.h"
#include "BlockPos.h"
#include "AABB.h"
#include "tools/MathTool.h"

using namespace SymHook;
void *globalPlayer = nullptr; //全局玩家对象
void *globalLevel = nullptr; //全局存档对象
void *globalDimension = nullptr; //全局维度对象
void *globalBlockSource = nullptr; //全局bs对象
void *globalSpawner = nullptr; //全局刷怪器对象
void *globalVillageManager = nullptr; //全局村庄管理器对象


//this code is from https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf



//粒子效果配置(性能配置)
int particleViewDistance = 128;
//等距切分坐标
bool enableMarkPos = false;
bool enableVillageShow = false;
bool enableExtraTickWork = true;
bool enableExplosion = true;
bool mobSpawnCounterStart = false;
int mobTickCounter = 0;

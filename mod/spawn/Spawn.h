#pragma once

#include "common/Trapdoor.h"
#include "lib/mod.h"
#include <random>

#define CHAR(S) reinterpret_cast<char*>(S)
using namespace SymHook;


struct SpawnConditions {



    bool isInWater();

    bool isInLava();

    bool isSurface();

    bool isUnderGround();

    int bright();

    BlockPos *position();
};

int getMobCount(void *sp);

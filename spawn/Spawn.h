#pragma once

#include "common/Common.h"
#include "lib/pch.h"
#include "lib/mod.h"
#include "commands/Shell.h"
#include <random>

using namespace SymHook;


bool isSlimeChunk(INT32 x, INT32 z) {
    //todo:  slime generate algorithm
    return false;
}

int getMobCount(void *sp) {
    if (!sp)return -1;
    return *(reinterpret_cast<UINT32 *>(sp) + 48);
}

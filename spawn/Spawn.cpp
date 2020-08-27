//
// Created by xhy on 2020/8/25.
//

#include "Spawn.h"

bool isSlimeChunk(INT32 x, INT32 z) {
    //todo:  slime generate algorithm
    return false;
}

int getMobCount(void *sp) {
    if (!sp)return -1;
    return *(reinterpret_cast<UINT32 *>(sp) + 48);
}

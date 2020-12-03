//
// Created by xhy on 2020/10/31.
//

#ifndef TRAPDOOR_PLAYERBUFFER_H
#define TRAPDOOR_PLAYERBUFFER_H

#include "common/BlockPos.h"
#include "Actor.h"
#include "Player.h"

struct PlayerBuffer {
    BlockPos pos1;
    BlockPos pos2;
    BlockPos rightPosition;
    bool operator<(const PlayerBuffer &rhs) const;
};


#endif //TRAPDOOR_PLAYERBUFFER_H

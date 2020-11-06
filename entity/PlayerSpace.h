//
// Created by xhy on 2020/10/31.
//

#ifndef TRAPDOOR_PLAYERSPACE_H
#define TRAPDOOR_PLAYERSPACE_H

#include "common/BlockPos.h"
#include "entity/Actor.h"
#include "Player.h"
struct PlayerSpace {
    Actor *self{};
    std::string playerName;
    BlockPos lastRightClick;
    MeasureManager manager;
    bool operator<(const PlayerSpace &rhs) const;
};


#endif //TRAPDOOR_PLAYERSPACE_H

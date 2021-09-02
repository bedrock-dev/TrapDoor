//
// Created by xhy on 2020/10/29.
//

#ifndef TRAPDOOR_GAMETICK_H
#define TRAPDOOR_GAMETICK_H

#include <chrono>
#include <vector>

#include "SimpleProfiler.h"
#include "entity/Actor.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/Message.h"
#include "village/Village.h"

namespace mod::tick {
    enum WorldTickStatus { Frozen, Normal, Slow, Forward, Wrap };

    WorldTickStatus getTickStatus();

    void freezeTick();

    void resetTick();

    void wrapTick(size_t wrapSpeed);

    void forwardTick(size_t tickNum);

    void slowTick(size_t slowSpeed);

    void profileWorld(trapdoor::Actor *player, int round = 0);

    void profileEntities(trapdoor::Actor *player);

    void queryStatus(trapdoor::Actor *player);

    void registerTickCommand(trapdoor::CommandManager &commandManager);

    void registerProfileCommand(trapdoor::CommandManager &commandManager);

    void mspt();
}  // namespace mod::tick

#endif  // TRAPDOOR_GAMETICK_H

//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_SHELL_H
#define TRAPDOOR_SHELL_H
#pragma once

#include "lib/pch.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "village/Village.h"
#include <map>
#include "spawn/Spawn.h"
#include <vector>
#include <sstream>
#include "tick/Tick.h"
#include "entity/Actor.h"
/*
 * Dirty Command Parser
 * if else
 */

using namespace SymHook;
enum class CmdType {
    Tick,
    TickForward,
    TickFreeze,
    TickSlow,
    TickReset,
    Profile,
    Village,
    Function,
    Position,
    Help,
    Spawn,
    Config
};
typedef CmdType ParaType;


std::vector<std::string> tokenize(std::string &commandString);

#endif //TRAPDOOR_SHELL_H

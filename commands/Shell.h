//
// Created by xhy on 2020/8/26.
//

#ifndef TRAPDOOR_SHELL_H
#define TRAPDOOR_SHELL_H

#include <vector>
#include <string>

enum class CmdType {
    Tick,
    Mspt,
    Profile,
    Village,
    Function,
    Help,
    Spawn,
    Config,
    Counter,
    Rand
};
typedef CmdType ParaType;

void initCommand();

#endif //TRAPDOOR_SHELL_H

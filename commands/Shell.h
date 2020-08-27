//
// Created by xhy on 2020/8/26.
//

#ifndef TRAPDOOR_SHELL_H
#define TRAPDOOR_SHELL_H
#include <vector>
#include <string>
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
std::vector <std::string> tokenize(std::string &commandString);

#endif //TRAPDOOR_SHELL_H

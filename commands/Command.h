//
// Created by xhy on 2020/8/26.
//

#ifndef TRAPDOOR_COMMAND_H
#define TRAPDOOR_COMMAND_H

#include "CommandNode.h"
#include <string>

void initCommand();

void regMCBECommand(const std::string &command, const char *description, CMD_LEVEL level);

#endif //TRAPDOOR_COMMAND_H

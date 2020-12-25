//
// Created by xhy on 2020/8/26.
//

#ifndef TRAPDOOR_COMMAND_H
#define TRAPDOOR_COMMAND_H

#include "CommandNode.h"
#include <string>

//初始化命令
namespace trapdoor{
//注册mcbe命令,说白了就是给一级指令加tab功能
void regMCBECommand(const std::string &command, const char *description, CMD_LEVEL level);
}
#endif //TRAPDOOR_COMMAND_H

//
// Created by xhy on 2020/10/24.
//

#ifndef COMMANDMANAGER_COMMANDMANAGER_H
#define COMMANDMANAGER_COMMANDMANAGER_H


#define EXE(S) execute([](ArgHolder *holder){S})
#define  ARG(arg, type, work) Arg(arg, ArgType::type)->EXE(work)

#include <map>
#include <vector>
#include <sstream>
#include "CommandNode.h"
#include "entity/Actor.h"

std::vector<std::string> tokenize(std::string &commandString);

class CommandManager {
    const static std::string prefix;
    std::map<std::string, CommandNode *> commandList;
public:
    CommandNode *registerCmd(const std::string &cmd, ArgType type = ArgType::NONE);

    int parse(Actor *player, std::string cmd);
};

#endif //COMMANDMANAGER_COMMANDMANAGER_H

//
// Created by xhy on 2020/10/24.
//

#ifndef COMMANDMANAGER_COMMANDMANAGER_H
#define COMMANDMANAGER_COMMANDMANAGER_H


#define EXE(S) execute([](ArgHolder *holder,Actor *player){S})
#define  ARG(arg, desc, type, work) Arg(arg,desc,ArgType::type)->EXE(work)

#include <map>
#include <vector>
#include <sstream>
#include "CommandNode.h"
#include "entity/Actor.h"

std::vector<std::string> tokenize(std::string &commandString);

class CommandManager {
    std::map<std::string, CommandNode *> commandList;

public:
    CommandNode *registerCmd(const std::string &cmd,
                             const std::string &description = "no description",
                             CMD_LEVEL level = OP,
                             ArgType type = ArgType::NONE);

    int parse(Actor *player, std::string cmd);

    void printfHelpInfo(Actor *player);

    bool findCommand(const std::string &cmd);
};

#endif //COMMANDMANAGER_COMMANDMANAGER_H

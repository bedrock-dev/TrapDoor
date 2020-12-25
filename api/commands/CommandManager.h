//
// Created by xhy on 2020/10/24.
//

#ifndef COMMANDMANAGER_COMMANDMANAGER_H
#define COMMANDMANAGER_COMMANDMANAGER_H


#define EXE(S) execute([&](ArgHolder *holder,Actor *player){S})
#define  ARG(arg, desc, type, work) Arg(arg,desc,ArgType::type)->EXE(work)

#include <map>
#include <vector>
#include <sstream>
#include "CommandNode.h"
#include "entity/Actor.h"


namespace trapdoor {

    class CommandManager {
        std::map<std::string, CommandNode *> commandList;

    public:
        CommandNode *registerCmd(const std::string &cmd,
                                 const std::string &description = "no description",
                                 CMD_LEVEL level = OP,
                                 ArgType type = ArgType::NONE);

        //解析命令
        int parse(Actor *player, std::string cmd);

        //打印帮助信息
        void printfHelpInfo(Actor *player);

        //在当前命令列表里面查找命令
        bool findCommand(const std::string &cmd);
    };
}

#endif //COMMANDMANAGER_COMMANDMANAGER_H

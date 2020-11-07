//
// Created by xhy on 2020/10/24.
//

#include "CommandManager.h"
#include "tools/Message.h"

const std::string CommandManager::prefix = "./";

int CommandManager::parse(Actor *player, std::string cmd) {
    if (cmd.rfind(prefix, 0) != 0)return -1;
    auto tokens = tokenize(cmd);
    printf("\n");
    if (tokens.empty())return -2;
    auto iter = this->commandList.find(tokens[0]);
    if (iter != commandList.end())
        return iter->second->parse(player, tokens, 1);
    error(player, "can't find command \"%s\",please type ./help for help", tokens[0].c_str());
    return -3;
}

CommandNode *CommandManager::registerCmd(const std::string &cmd, ArgType type) {
    auto *rootNode = new CommandNode(cmd);
    rootNode->setArgType(type);
    commandList[cmd] = rootNode;
    printf("register command     [%s]\n", cmd.c_str());
    return rootNode;
}

std::vector<std::string> tokenize(std::string &commandString) {
    std::vector<std::string> tokens;
    std::stringstream str(commandString);
    std::string command;
    while (str >> commandString)
        tokens.push_back(commandString);
    return tokens;
}

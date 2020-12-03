//
// Created by xhy on 2020/10/24.
//

#include "CommandManager.h"
#include "tools/Message.h"
#include "tools/DirtyLogger.h"
#include "Command.h"

int CommandManager::parse(Actor *player, std::string cmd) {
    auto tokens = tokenize(cmd);
    if (tokens.empty())return -1;
    auto iter = this->commandList.find(tokens[0]);
    if (iter != commandList.end()) {
        auto level = iter->second->getPermissionLevel();
        if (level <= player->getCommandLevel()) {
            return iter->second->parse(player, tokens, 1);
        } else {
            error(player, "you have no permission to run this command");
            return -2;
        }
    }
    return -3;
}

CommandNode *
CommandManager::registerCmd(const std::string &cmd, const std::string &description, CMD_LEVEL level, ArgType type) {
    //创建当前命令的根节点
    auto *rootNode = new CommandNode(cmd, description, level);
    rootNode->setArgType(type);
    commandList["/" + cmd] = rootNode; //加个/方便查找
    //给根节点添加一个默认的?选项方便打印帮助信息
    auto *helpNode = new CommandNode("?", "print help info", MEMBER);
    //打印帮助信息
    helpNode->execute([rootNode](ArgHolder *holder, Actor *player) {
        // dbg("print help info");
        rootNode->printHelpInfo(0, player);
    });
    rootNode->then(helpNode);
    //注册命令到游戏中
    L_INFO("register command %s", cmd.c_str());
    regMCBECommand(cmd, description.c_str(), level);
    // LOGF(getLogFile(), "register command [%s]\n", cmd.c_str());
    return rootNode;
}

bool CommandManager::findCommand(const string &cmd) {
    std::string buff(cmd);
    auto tokens = tokenize(buff);
    if (tokens.empty())return false;
    return this->commandList.find(tokens[0]) != this->commandList.end();
}

void CommandManager::printfHelpInfo(Actor *actor) {
    for (const auto &cmd :this->commandList) {
        cmd.second->printHelpInfo(0, actor);
    }
}


std::vector<std::string> tokenize(std::string &commandString) {
    std::vector<std::string> tokens;
    std::stringstream str(commandString);
    std::string command;
    while (str >> commandString)
        tokens.push_back(commandString);
    return tokens;
}

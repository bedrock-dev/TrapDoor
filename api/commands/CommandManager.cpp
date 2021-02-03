//
// Created by xhy on 2020/10/24.
//

#include "CommandManager.h"
#include "tools/Message.h"
#include "tools/DirtyLogger.h"
#include "Command.h"

namespace trapdoor {
    namespace {
        //字符串转为tokens列表
        std::vector<std::string> tokenize(std::string &commandString) {
            std::vector<std::string> tokens;
            std::stringstream str(commandString);
            std::string command;
            while (str >> commandString)
                tokens.push_back(commandString);
            return tokens;
        }
    }

    //解析玩家命令字符串
    int CommandManager::parse(Actor *player, std::string cmd) {
        auto tokens = tokenize(cmd);
        if (tokens.empty())return -1;
        auto iter = this->commandList.find(tokens[0]);
        if (iter != commandList.end()) {
            //这里进行权限检查
            if (!this->checkCommandPermission(tokens[0], player)) {
                return -2;
            }
            //检查通过转发给命令解析器
            return iter->second->parse(player, tokens, 1);
        }
        return -3;
    }

    //注册命令
    CommandNode *
    CommandManager::registerCmd(const std::string &cmd, const std::string &description, CommandPermissionLevel level,
                                ArgType type) {
        //创建当前命令的根节点
        auto *rootNode = new CommandNode(cmd, description);
        rootNode->setArgType(type);
        commandList["/" + cmd] = rootNode; //加个/方便查找
        //给根节点添加一个默认的?选项方便打印帮助信息
        auto *helpNode = new CommandNode("?", "print help info");
        //打印帮助信息
        helpNode->execute([rootNode](ArgHolder *holder, Actor *player) {
            rootNode->printHelpInfo(0, player);
        });
        rootNode->then(helpNode);
        //注册命令到游戏中
        L_INFO("register command %s", cmd.c_str());
        regMCBECommand(cmd, description.c_str(), level, true);
        return rootNode;
    }

    bool CommandManager::findCommand(const std::string &cmd) {
        std::string buff(cmd);
        auto tokens = tokenize(buff);
        if (tokens.empty())return false;
        return this->commandList.find(tokens[0]) != this->commandList.end();
    }

//递归打印命令帮助
    void CommandManager::printfHelpInfo(Actor *actor) {
        for (const auto &cmd :this->commandList) {
            cmd.second->printHelpInfo(0, actor);
        }
    }

    bool CommandManager::checkCommandPermission(const std::string &command, Actor *player) {
        if (!this->enablePermissionCheck)
            return true;
        auto cmdCfg = this->commandConfigList.find(command);
        if (cmdCfg == commandConfigList.end()) {
            L_WARNING("command %s was not config", command.c_str());
            error(player, "这个命令没有被配置，请联系腐竹");
            return false;
        }
        //todo game mode check

        if (!cmdCfg->second.enable) {
            error(player, "该服务器未启用该指令,请联系腐竹");
            return false;
        }

        //todo level cheat check;

        auto playerLevel = static_cast<int>(player->getCommandLevel());
        auto commandLevel = static_cast<int>(cmdCfg->second.permissionLevel);
        if (playerLevel < commandLevel) {
            L_DEBUG("server reject the execute of command [%s] for player %s", command.c_str(),
                    player->getNameTag().c_str());
            error(player, "你没有权限执行该命令[你的等级:%d < 命令等级:%d]", playerLevel, commandLevel);
            return false;
        }
        return true;
    }


    void CommandManager::setCommandConfig(std::map<std::string, CommandConfig> &cmdConfigList) {
        this->commandConfigList = cmdConfigList;
        L_INFO("set command permission info");

    }

    void CommandManager::runVanillaCommand(const std::string &command) {
        //todo
    }

}

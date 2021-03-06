//
// Created by xhy on 2020/10/24.
//

#include "CommandManager.h"
#include "tools/Message.h"
#include "tools/DirtyLogger.h"
#include "Command.h"
#include "mod.h"

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
            std::string s;
            rootNode->getHelpInfo(0, s);
            trapdoor::info(player, s);
        });
        rootNode->then(helpNode);
        //注册命令到游戏中
        L_DEBUG("register command %s", cmd.c_str());
        regMCBECommand(cmd, LANG(description).c_str(), level, true);
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
        std::string buffer;
        for (const auto &cmd :this->commandList) {
            //只打印自己有权限执行的指令
            if (!this->enablePermissionCheck || this->checkCommandPermission(cmd.first, actor, false))
                cmd.second->getHelpInfo(0, buffer);
        }
        trapdoor::info(actor, buffer);
    }

    bool CommandManager::checkCommandPermission(const std::string &command, Actor *player, bool showInfo) {
        if (!this->enablePermissionCheck)
            return true;
        auto cmdCfg = this->commandConfigList.find(command);
        if (cmdCfg == commandConfigList.end()) {
            L_WARNING("command %s was not config", command.c_str());
            if (showInfo)
                error(player, LANG("command.error.config"));
            return false;
        }
        //todo game mode check

        if (!cmdCfg->second.enable) {
            if (showInfo)
                error(player, LANG("command.error.config"));
            return false;
        }

        //todo level cheat check;

        auto playerLevel = static_cast<int>(player->getCommandLevel());
        auto commandLevel = static_cast<int>(cmdCfg->second.permissionLevel);
        if (playerLevel < commandLevel) {

            if (showInfo) {
                L_DEBUG("server reject the execute of command [%s] for player %s", command.c_str(),
                        player->getNameTag().c_str());
                error(player, LANG("command.error.permission"), playerLevel, commandLevel);
            }
            return false;
        }
        return true;
    }


    void CommandManager::setCommandConfig(std::map<std::string, CommandConfig> &cmdConfigList) {
        this->commandConfigList = cmdConfigList;
        L_DEBUG("set command permission info");

    }

    using namespace SymHook;

    //获取指令队列
    static VA cmdQueue = 0;
    THook(VA,
          MSSYM_MD5_3b8fb7204bf8294ee636ba7272eec000,
          VA _this
          ){
        cmdQueue = original(_this);
        return cmdQueue;
    }

    //执行原版指令
    bool CommandManager::runVanillaCommand(const std::string &command) {
        if (cmdQueue != 0) {
            SYM_CALL(bool(*) (VA, std::string),
                     MSSYM_MD5_b5c9e566146b3136e6fb37f0c080d91e,
                     cmdQueue,
                     command
                     );
            return true;
        }
        return false;
    }

}

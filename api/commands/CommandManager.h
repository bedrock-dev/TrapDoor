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
#include "tools/noncopyable .h"


namespace trapdoor {

    struct CommandConfig {
        bool enable = true; //是否启用
        CommandPermissionLevel permissionLevel = Admin; //权限等级
        //下面两个还没启用，主要是还没获取游戏模式的接口（设置游戏模式的都有了）
        bool needCheat = false;
        bool survival = false; //生存中是否可用
    };

    class CommandManager : public trapdoor::noncopyable {
        //命令列表
        std::map<std::string, CommandNode *> commandList;
        //命令配置文件列表
        std::map<std::string, CommandConfig> commandConfigList;
    public:
        CommandNode *registerCmd(const std::string &cmd,
                                 const std::string &description = "no description",
                                 CommandPermissionLevel level = Any,
                                 ArgType type = ArgType::NONE);

        bool enablePermissionCheck = true;

        //解析命令
        int parse(Actor *player, std::string cmd);

        inline void setEnablePermissionCheck(bool able) {
            this->enablePermissionCheck = able;
        }

        //设置命令配置
        void setCommandConfig(std::map<std::string, CommandConfig> &cmdConfigList);

        //打印帮助信息
        void printfHelpInfo(Actor *player);

        //在当前命令列表里面查找命令
        bool findCommand(const std::string &cmd);

        //检查权限等级
        bool checkCommandPermission(const std::string &command, Actor *player, bool showInfo = true);

        //执行原版命令
        static bool runVanillaCommand(const std::string &command);
    };

}

typedef trapdoor::CommandManager CommandManager;

#endif //COMMANDMANAGER_COMMANDMANAGER_H

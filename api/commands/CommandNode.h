//
// Created by xhy on 2020/10/23.
// 命令节点,有一说一这是整个插件逻辑最复杂的代码了。
//

#ifndef COMMANDMANAGER_COMMANDNODE_H
#define COMMANDMANAGER_COMMANDNODE_H

#include <map>
#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <vector>
#include "ArgHolder.h"

enum class ArgType {
    INT,
    BOOL,
    STR,
    NONE
};


/*
 * 命令节点
 * 存储当前命令节点的命令名
 * 描述信息(方便生成帮助信息)
 * 命令等级(暂未实装)
 * 行为
 * 下一级命令节点等等
 */
namespace trapdoor {
    class Actor;
    enum PlayerPermissionLevel {
        Visitor = 0,
        Member = 1,
        Operator = 2,
        Custom = 3
    };

    enum CommandPermissionLevel : uint8_t {
        Any = 0, //Tell
        GameMasters = 1,
        Admin = 2,
        Host = 3,
        Owner = 4,
        Internal = 5
    };

    inline const char *commandPermissionLevelToStr(CommandPermissionLevel level);

    enum CommandFlag1 : uint8_t {
        None = 0,
        Message = 0x20
    };

    inline const char *CommandFlag1ToStr(CommandFlag1 flag1) {
        switch (flag1) {
            case None:
                return "None";
            case Message:
                return "Message";
            default:
                return "Unknown";
        }
    }


    enum CommandFlag2 : uint8_t {
        Cheat = 0x0,
        NoCheat = 0x40,
    };

    inline const char *CommandFlag2ToStr(CommandFlag2 flag2) {
        switch (flag2) {
            case Cheat:
                return "cheat";
            case NoCheat:
                return "noCheat";
            default:
                return "none";
        }
    }

    class CommandNode {
        std::string name;
        std::string description;
        std::map<std::string, CommandNode *> nextNodes;
        std::function<void(ArgHolder *, Actor *)> work;
        ArgType argType = ArgType::NONE;

    public:
        explicit CommandNode(std::string name);

        CommandNode(std::string name, std::string description);

        CommandNode *execute(const std::function<void(ArgHolder *, Actor *)> &task) {
            this->work = task;
            return this;
        }

        inline std::string getName() const {
            return this->name;
        }

        inline void setArgType(ArgType type) {
            this->argType = type;
        }

        CommandNode *then(CommandNode *node);

        void printHelpInfo(int idx, Actor *actor) const;

        std::string getDescription() const;

        int parse(Actor *player, const std::vector<std::string> &tokens, size_t idx);

        void run(ArgHolder *holder, Actor *player);
    };

    CommandNode *Arg(const std::string &args, const std::string &desc, ArgType type = ArgType::NONE);
}
#endif //COMMANDMANAGER_COMMANDNODE_H

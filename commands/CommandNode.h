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

class Actor;

enum class ArgType {
    INT,
    BOOL,
    STR,
    NONE
};

//这个枚举是根据观察原版命令注册过程得出的
enum CMD_LEVEL {
    DEFAULT = 0,    //不开作弊的时候普通玩家可以使用的的命令 /tell /say /list .etc
    CHEAT = 1,      //开作弊的时候可以使用的命令 /fill /setblock .etc
    OP = 2,         //op相关的指令 /op /deop..
    BACKEND = 3,    //只能在服务器后台执行的指令 /save /stop .etc
    DEVELOP = 4    //没有公开发表的指令 /change-settings
};

class CommandNode {
    std::string name;
    std::string description;
    CMD_LEVEL permissionLevel = DEFAULT;
    std::map<std::string, CommandNode *> nextNode;
    std::function<void(ArgHolder *, Actor *)> work;
    ArgType argType = ArgType::NONE;

public:
    explicit CommandNode(std::string name);

    CommandNode(std::string name, CMD_LEVEL level);

    CommandNode(std::string name, std::string description, CMD_LEVEL level);


    CommandNode *execute(const std::function<void(ArgHolder *, Actor *)> &task) {
        this->work = task;
        return this;
    }


    std::string getName() const {
        return this->name;
    }

    void setArgType(ArgType type) {
        this->argType = type;
    }

    CommandNode *then(CommandNode *node);

    void printHelpInfo(int idx, Actor *actor) const;

    std::string getDescription() const;

    int parse(Actor *player, const std::vector<std::string> &tokens, size_t idx);
};

CommandNode *Arg(const std::string &args, ArgType type = ArgType::NONE);

bool isValidIntString(const std::string &str);

#endif //COMMANDMANAGER_COMMANDNODE_H

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
    MEMBER = 0,
    OP = 1,
    BACK_EBD = 2,
    DEVELOP = 3,
    MOJANG = 4
};


std::string cmdLevelToStr(CMD_LEVEL level);

/*
 * 命令节点
 * 存储当前命令节点的命令名
 * 描述信息(方便生成帮助信息)
 * 命令等级(暂未实装)
 * 行为
 * 下一级命令节点等等
 */
class CommandNode {
    std::string name;
    std::string description;
    CMD_LEVEL permissionLevel = OP;
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


    inline std::string getName() const {
        return this->name;
    }

    inline void setArgType(ArgType type) {
        this->argType = type;
    }

    inline CMD_LEVEL getPermissionLevel() const {
        return this->permissionLevel;
    }

    CommandNode *then(CommandNode *node);

    void printHelpInfo(int idx, Actor *actor) const;

    std::string getDescription() const;

    int parse(Actor *player, const std::vector<std::string> &tokens, size_t idx);

    void run(ArgHolder *holder, Actor *player);
};

CommandNode *Arg(const std::string &args, const std::string &desc, ArgType type = ArgType::NONE);

#endif //COMMANDMANAGER_COMMANDNODE_H

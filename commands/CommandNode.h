//
// Created by xhy on 2020/10/23.
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

class CommandNode {
    std::string name;
    std::map<std::string, CommandNode *> nextNode;
    std::function<void(ArgHolder *, Actor *)> work;
    ArgType argType = ArgType::NONE;

public:
    explicit CommandNode(std::string name);

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

    void print(int idx) const;

    int parse(Actor *player, const std::vector<std::string> &tokens, size_t idx);
};

CommandNode *Arg(const std::string &args, ArgType type = ArgType::NONE);

bool isValidIntString(const std::string &str);

#endif //COMMANDMANAGER_COMMANDNODE_H

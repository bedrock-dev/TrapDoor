//
// Created by xhy on 2020/10/23.
//

#include "CommandNode.h"
#include "tools/Message.h"
#include <algorithm>
#include "entity/Actor.h"

CommandNode *Arg(const std::string &args, ArgType type) {
    auto *node = new CommandNode(args);
    node->setArgType(type);
    return node;
}


bool isValidIntString(const std::string &str) {
    return std::all_of(str.begin(), str.end(), [](char c) { return '0' <= c && c <= '9'; });
}

CommandNode::CommandNode(std::string name) : name(std::move(name)),
                                             work([&name](ArgHolder *holder, Actor *actor) {
                                                 error(actor, "require a sub command behind %s", name.c_str());
                                             }) {}


int CommandNode::parse(Actor *player, const std::vector<std::string> &tokens, size_t idx) {
    bool executeNow = false;
    if (idx == tokens.size()) { //当前位置已经没tokens了
        executeNow = true;
        if (this->argType == ArgType::NONE) {
            ArgHolder holder(0);
            this->work(&holder, player);
        } else {
            error(player, "require an parameter behind \"%s\"", tokens[idx - 1].c_str());
        }
    } else if (idx == tokens.size() - 1) { //当前是最后一个token
        ArgHolder *holder = nullptr;
        switch (this->argType) {
            case ArgType::INT:
                executeNow = isValidIntString(tokens[idx]);
                holder = integerArg(strtol(tokens[idx].c_str(), nullptr, 10));
                break;
            case ArgType::BOOL:
                executeNow =
                        tokens[idx] == "true" || tokens[idx] == "false" || tokens[idx] == "1" || tokens[idx] == "0";
                holder = boolArg(tokens[idx] == "true" || tokens[idx] == "1");
                break;
            case ArgType::STR:
                executeNow = true;
                holder = strArg(tokens[idx]);
                break;
            case ArgType::NONE:
                executeNow = false;
                break;
        }
        if (executeNow) {
            this->work(holder, player);
            delete holder;
        }
    }
    if (!executeNow) {
        for (const auto &node:this->nextNode) {
            if (node.second->getName() == tokens[idx]) {
                return node.second->parse(player, tokens, idx + 1);
            }
        }
        std::string s = std::string("no sub command [ ") + tokens[idx] + " ]\n";
        for (auto &node:this->nextNode) {
            s += "[";
            s += node.first;
            s += "] ";
        }
        error(player, "%s", s.c_str());
    }
    return 0;
}

void CommandNode::print(int idx) const {
    std::string space(idx * 4, ' ');
    std::cout << space << this->getName() << std::endl;
    for (auto &node: this->nextNode) {
        node.second->print(idx + 1);
    }
}

CommandNode *CommandNode::then(CommandNode *node) {
    this->nextNode[node->getName()] = node;
    return this;
}

//
// Created by xhy on 2020/10/23.
//

#include "CommandNode.h"
#include "tools/Message.h"
#include <algorithm>
#include <utility>
#include "tools/MsgBuilder.h"


namespace trapdoor {
    CommandNode *Arg(const std::string &args, const std::string &desc, ArgType type) {

        auto *node = new CommandNode(args, desc, OP);
        node->setArgType(type);
        return node;
    }


    static bool isValidIntString(const std::string &str) {
        return std::all_of(str.begin(), str.end(), [](char c) { return '0' <= c && c <= '9'; });
    }

    std::string cmdLevelToStr(CMD_LEVEL level) {
        switch (level) {
            case MEMBER:
                return "member";
            case OP:
                return "ops";
            case BACK_EBD:
                return "back_end";
            case DEVELOP:
                return "develop";
            case MOJANG:
                return "mojang";
            default:
                return "unknown";
        }
    }

    CommandNode::CommandNode(std::string name, std::string description, CMD_LEVEL level)
            : name(std::move(name)),
              work([&name](ArgHolder *holder, Actor *actor) {
                  error(actor, "require a sub command behind %s", name.c_str());
              }),
              description(std::move(description)),
              permissionLevel(level) {
    }

    CommandNode::CommandNode(std::string name, CMD_LEVEL level) : CommandNode(
            std::move(name), "no desc", level) {}

    CommandNode::CommandNode(std::string name) : CommandNode(std::move(name), OP) {}

    int CommandNode::parse(Actor *player, const std::vector<std::string> &tokens, size_t idx) {
        bool executeNow = false;
        if (idx == tokens.size()) { //当前位置已经没tokens了
            executeNow = true;
            if (this->argType == ArgType::NONE) {
                ArgHolder holder(0);
                this->run(&holder, player);
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
                this->run(holder, player);
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

    void CommandNode::printHelpInfo(int idx, Actor *actor) const {
        if (this->getName() == "?")return;

        MessageBuilder builder;
        if (idx != 0) {
            builder += std::string(idx * 4, ' ');
        }

        builder.sText(this->getName(), MSG_COLOR::YELLOW | MSG_COLOR::BOLD);
        builder += " [";
        switch (this->argType) {
            case ArgType::NONE:
                builder += "none";
                break;
            case ArgType::INT:
                builder += "integer";
                break;
            case ArgType::BOOL:
                builder += "true/false";
                break;
            case ArgType::STR:
                builder += "string";
                break;
        }
        builder += "] - ";
        builder += this->getDescription();
        builder.send(actor);
        for (auto &node: this->nextNode) {
            node.second->printHelpInfo(idx + 1, actor);
        }
    }

    CommandNode *CommandNode::then(CommandNode *node) {
        this->nextNode[node->getName()] = node;
        return this;
    }

    std::string CommandNode::getDescription() const {
        return this->description;
    }

    void CommandNode::run(ArgHolder *holder, Actor *player) {
        if (!player)return;
        this->work(holder, player);

    }

}
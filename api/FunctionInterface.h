//
// Created by xhy on 2021/4/29.
//

#ifndef MOD_FUNCTIONINTERFAACE_H
#define MOD_FUNCTIONINTERFAACE_H

#include <string>
#include "commands/CommandManager.h"

class FunctionInterface {
protected:
    std::string name;
    bool enable = false;
public:

    getName() const { return this->name; }

    void tick() = 0;

    void setAble(bool able) { this->enable = able; }

    void registerCommand(CommandManager &commandManager) = 0;

};


#endif //MOD_FUNCTIONINTERFAACE_H

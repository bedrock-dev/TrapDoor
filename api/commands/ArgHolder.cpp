//
// Created by xhy on 2020/10/23.
//

#include "ArgHolder.h"

namespace trapdoor {
    ArgHolder *integerArg(int val) {
        return new ArgHolder(val);
    }


    ArgHolder *strArg(const std::string &val) {
        return new ArgHolder(val);
    }

    ArgHolder *boolArg(bool val) {
        return new ArgHolder(val);
    }

    bool ArgHolder::getBool() const {
        return boolVal;
    }

    std::string ArgHolder::getString() const {
        return strVal;
    }

    int ArgHolder::getInt() const {
        return intVal;
    }
}


//
// Created by xhy on 2020/10/23.
//

#include "ArgHolder.h"

ArgHolder *integerArg(int val) {
    return new ArgHolder(val);
}

ArgHolder *floatArg(float val) {
    return new ArgHolder(val);
}

ArgHolder *strArg(const std::string &val) {
    return new ArgHolder(val);
}

ArgHolder *boolArg(bool val) {
    return new ArgHolder(val);
}

bool ArgHolder::getBool() const {
    return this->boolVal;
}

std::string ArgHolder::getString() const {
    return strVal;
}

float ArgHolder::getFloat() const {
    return floatVal;
}

int ArgHolder::getInt() const {
    return intVal;
}

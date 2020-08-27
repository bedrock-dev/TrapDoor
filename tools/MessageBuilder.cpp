//
// Created by xhy on 2020/8/25.
//
#include "MessageBuilder.h"

MessageBuilder &MessageBuilder::Text(const std::string &s) {
    messageBuffer.emplace_back(s);
    return *this;
}

MessageBuilder &MessageBuilder::pos() {
    return *this;
}

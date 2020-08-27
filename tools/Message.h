//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MESSAGE_H
#define TRAPDOOR_MESSAGE_H

#include "lib/mod.h"
#include "common/Common.h"
#include "dbg.h"
#include "../lib/pch.h"

using namespace SymHook;

void sendLocalMessage(std::string &s, void *player);

template<typename ... Args>
void gamePrintf(const std::string &format, Args ... args) {
    if (!globalPlayer)return;
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
    if (size <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    auto str = std::string(buf.get(), buf.get() + size - 1);
    sendLocalMessage(str, globalPlayer);
}

void info(const std::string &message);

void error(const std::string &message);

void warning(const std::string &message);


#endif //TRAPDOOR_MESSAGE_H

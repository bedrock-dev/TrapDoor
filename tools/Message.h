//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MESSAGE_H
#define TRAPDOOR_MESSAGE_H

#include "lib/pch.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "common/Common.h"

namespace SymHook {
    void sendLocalMessage( std::string &s, void *player) {
        std::vector<std::string> v;
        v.emplace_back("test");
        SYM_CALL(
                void(*)(bool, void *, std::string &, std::vector<std::string> &),
                MSSYM_MD5_24be62e9330073695808606844de0d99,
                true, player, s, v);
    }
}

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
    SymHook::sendLocalMessage(str, globalPlayer);
}

void info(const std::string &message) {
    gamePrintf("%s", message.c_str());
}

void error(const std::string &message) {
    gamePrintf("§c%s", message.c_str());
}

void warning(const std::string &message) {
    gamePrintf("§6%s", message.c_str());
}


#endif //TRAPDOOR_MESSAGE_H

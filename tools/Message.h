//
// Created by xhy on 2020/10/31.
//

#ifndef TRAPDOOR_MESSAGE_H
#define TRAPDOOR_MESSAGE_H

#include "lib/mod.h"
#include "dbg.h"
#include "lib/pch.h"
#include "level/Level.h"
#include "common/Trapdoor.h"
#include <string>

class Actor;

void mcbe_sendMessage(std::string &s, Actor *player);


template<typename ... Args>
std::string stringFmt(const std::string &format, Args ... args) {
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size <= 0) {
        return std::string("");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template<typename ... Args>
void gamePrintf(Actor *player, const std::string &prefix, const std::string &format, Args ... args) {
    auto str = prefix + stringFmt(format, args...);
    mcbe_sendMessage(str, player);
}

template<typename ... Args>
void waring(Actor *player, const std::string &format, Args ... args) {
    gamePrintf(player, "§6", format, args...);
}

template<typename ... Args>
void error(Actor *player, const std::string &format, Args ... args) {
    gamePrintf(player, "§c", format, args...);
}

template<typename ... Args>
void info(Actor *player, const std::string &format, Args ... args) {
    gamePrintf(player, "", format, args...);
}

template<typename ... Args>
void broadcastMsg(const std::string &format, Args ... args) {
    auto msg = "[TD BR] " + stringFmt(format, args...);
    globalLevel->forEachPlayer([&msg](Actor *player) {
        mcbe_sendMessage(msg, player);
    });
}



#endif //TRAPDOOR_MESSAGE_H

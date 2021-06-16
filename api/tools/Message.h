//
// Created by xhy on 2020/10/31.
//

#ifndef TRAPDOOR_MESSAGE_H
#define TRAPDOOR_MESSAGE_H

#include "world/Level.h"
#include "BDSMod.h"
#include <string>
#include "lib/Loader.h"

#define STR(x) #x
#define C_DARK_RED(x) "§4" STR(x) "§r"
#define C_RED(x) "§c" STR(x) "§r"
#define C_GOLD(x) "§6" STR(x) "§r"
#define C_YELLOW(x) "§e" STR(x) "§r"
#define C_GREEN(x) "§a" STR(x) "§r"
#define C_AQUA(x) "§b" STR(x) "§r"
#define C_BLUE(x) "§9" STR(x) "§r"
#define C_LIGHT_PURPLE(x) "§d" STR(x) "§r"
#define C_WHITE(x) "§f" STR(x) "§r"
#define C_GRAY(x) "§7" STR(x) "§r"
#define  C_BLACK(x) "§0" STR(x) "§r"
#define C_BOLD(x) "§l" STR(x) "§r"
#define C_ITALIC  "§o" STR(x) "§r"
#define C_INT C_GREEN( %d )
#define C_FLOAT C_GREEN( %.3f )
#define C_POS C_AQUA(%d %d %d)
#define C_VEC3 C_LIGHT_PURPLE(%.2f %.2f %.2f)
namespace trapdoor {
    class Actor;


    void mcbe_sendMessage(const std::string &s, Actor *player);

    template<typename ... Args>
    std::string format(const std::string &format, Args ... args) {
        int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size <= 0)
            return "";
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }

    template<typename ...Args>
    void gamePrintf(Actor *player, const std::string &prefix, const std::string &fmt, Args ...args) {
        const std::string message = prefix + format(fmt, args...);
        mcbe_sendMessage(message, player);
    }


    template<typename ... Args>
    void warning(Actor *player, const std::string &format, Args ... args) {
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
    void broadcastMsg(const std::string &fmt, Args... args) {
        auto msg = format(fmt, args...);
        trapdoor::bdsMod->getLevel()->forEachPlayer([&msg](Actor *player) {
            mcbe_sendMessage(msg, player);
        });
    }

}


#endif //TRAPDOOR_MESSAGE_H

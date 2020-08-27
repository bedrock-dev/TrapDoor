//
// Created by xhy on 2020/8/25.
//

#include "Message.h"

void warning(const std::string &message) {
    gamePrintf("§6%s", message.c_str());
}

void error(const std::string &message) {
    gamePrintf("§c%s", message.c_str());
}

void info(const std::string &message) {
    gamePrintf("%s", message.c_str());
}

void sendLocalMessage(std::string &s, void *player) {
    std::vector<std::string> v;
    v.emplace_back("test");
    SYM_CALL(
            void(*)(bool, void *, std::string &, std::vector<std::string> &),
            MSSYM_MD5_24be62e9330073695808606844de0d99,
            true, player, s, v);
}

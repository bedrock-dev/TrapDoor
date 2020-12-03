//
// Created by xhy on 2020/8/25.
//

#include "Message.h"
#include <cstdarg>

using namespace SymHook;

void mcbe_sendMessage(std::string &s, Actor *player) {
    if (!player)return;
    std::vector<std::string> v;
    v.emplace_back("test");
    SYM_CALL(
            void(*)(bool, Actor *, std::string &, std::vector<std::string> &),
            MSSYM_MD5_24be62e9330073695808606844de0d99,
            true, player, s, v);
}



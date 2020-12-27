//
// Created by xhy on 2020/8/25.
//

#include "Message.h"
#include <cstdarg>
#include "DirtyLogger.h"
#include "lib/SymHook.h"
#include "entity/Actor.h"

namespace trapdoor {
    using namespace SymHook;


    void mcbe_sendMessage(const std::string &s, Actor *player) {
        if (!player) {
            L_DEBUG("send message [%s] to a nullptr player", s.c_str());
            return;
        }
        L_DEBUG("send message [%s] to %s", s.c_str(), player->getNameTag().c_str());
        std::vector<std::string> v;
        v.emplace_back("test");
        SYM_CALL(
                void(*)(bool, Actor *,const std::string &, std::vector<std::string> &),
                MSSYM_MD5_24be62e9330073695808606844de0d99,
                true, player, s, v);
    }




}



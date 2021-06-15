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
        SymCall("?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic"
            "_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$bas"
            "ic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$ba"
            "sic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z", void,
            bool, Actor*, const std::string&, std::vector<std::string> &)(true, player, s, v);
    }

}



//
// Created by xhy on 2020/8/25.
//

#include "Message.h"

#include <cstdarg>

#include "DirtyLogger.h"
#include "entity/Actor.h"
#include "lib/SymHook.h"

namespace trapdoor {
    using namespace SymHook;

    void mcbe_sendMessage(const std::string &s, Actor *player) {
        if (!player) {
            L_DEBUG("send message [%s] to a nullptr player", s.c_str());
            return;
        }
        L_DEBUG("send message [%s] to %s", s.c_str(),
                player->getNameTag().c_str());
        std::vector<std::string> v;
        v.emplace_back("test");
        SYM_CALL(void (*)(bool, Actor *, const std::string &,
                          std::vector<std::string> &),
                 CommandUtils_displayLocalizableMessage_24be62e9, true, player,
                 s, v);
    }

}  // namespace trapdoor

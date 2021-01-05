//
// Created by xhy on 2021/1/3.
//

#ifndef MOD_PLAYERFUNCTION_H
#define MOD_PLAYERFUNCTION_H

#include <map>
#include <string>
#include "entity/Actor.h"

namespace mod {
    struct PlayerData {
        bool enableChunkBoundsShow = false;
    };

    class PlayerFunction {
        std::map<std::string, bool> enables;
        unsigned long long gameTick = 0;

        static void drawChunkBound(trapdoor::Actor *player);

    public:
        inline void setAble(const std::string &playerName, bool able) { enables[playerName] = able; }

        void tick();
    };

}


#endif //MOD_PLAYERFUNCTION_H

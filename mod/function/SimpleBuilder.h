//
// Created by xhy on 2021/1/5.
//

#ifndef MOD_SIMPLEBUILDER_H
#define MOD_SIMPLEBUILDER_H

#include "entity/Actor.h"
#include "block/BlockSource.h"
#include "tools/noncopyable .h"
#include "trapdoor.h"

namespace mod {
    class SimpleBuilder : noncopyable {
        size_t maxCircleRadius = 30000000;
        bool enable = false;
    public:
        inline void setAble(bool able) { this->enable = able; }

        inline void setMaxRadius(int radius) {
            this->maxCircleRadius = radius;
        }

        void buildSphere(trapdoor::Actor *player, size_t size, bool hollow) const;

        void buildCircle(trapdoor::Actor *player, size_t size, bool hollow) const;

        void registerDrawCommand(trapdoor::CommandManager &commandManager);
    };
}

#endif //MOD_SIMPLEBUILDER_H

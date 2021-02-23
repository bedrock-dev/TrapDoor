//
// Created by xhy on 2020/10/29.
//

#ifndef TRAPDOOR_LEVEL_H
#define TRAPDOOR_LEVEL_H

#include <vector>
#include "block/Block.h"
#include <cstdio>
#include <functional>

namespace trapdoor {
    class BlockPos;

    class Dimension;

    class Actor;

    class ActorUniqueID;




    class Tick {
    public:
        uint64_t tick;

        uint64_t operator%(size_t num) const { return tick % num; }

        bool operator<(const Tick &rhs) const {
            return tick < rhs.tick;
        }

        inline uint64_t getTimeStamp() const { return this->tick; }

        bool operator==(const Tick &rhs) const {
            return tick == rhs.tick;
        }

    };

    class Level {

    public:
        Level() = delete;

        void forEachPlayer(const std::function<void(Actor *)> &todo);


        Actor *getNearestPlayer(BlockPos &pos);


        Actor *getNearestDimensionPlayer(const BlockPos &pos, int dimID);


        Dimension *getDimFromID(int id);

        Actor *fetchEntity(const trapdoor::ActorUniqueID &id, bool b);


        uint64_t getGameTick();
    };
}

#endif //TRAPDOOR_LEVEL_H

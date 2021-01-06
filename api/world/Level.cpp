//
// Created by xhy on 2020/10/29.
//

#include "Level.h"
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "Dimension.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    using namespace SymHook;

    void Level::forEachPlayer(const std::function<void(Actor *)> &todo) {
        //!硬编码
        auto begin = (uint64_t *) *((uint64_t *) this + 11);
        auto end = (uint64_t *) *((uint64_t *) this + 12);
        while (begin != end) {
            auto *player = (Actor *) (*begin);
            if (player)todo(player);
            ++begin;
        }
    }

    Actor *Level::getNearestPlayer(BlockPos &pos) {
        Actor *nearest = nullptr;
        float minDistance = 512;
        this->forEachPlayer([&pos, &minDistance, &nearest](Actor *player) {
            BlockPos p(player->getPos()->x, player->getPos()->y, player->getPos()->z);
            auto d = p.distanceTo(pos);
            if (d < minDistance) {
                minDistance = d;
                nearest = player;
            }
        });
        return nearest;
    }

    Dimension *Level::getDimFromID(int id) {
        Dimension *dim = SYM_CALL(
                Dimension*(*)(Level * , int),
                MSSYM_B1QE12getDimensionB1AA5LevelB2AAE17QEBAPEAVDimensionB2AAA1VB2QDE11AutomaticIDB1AE10VDimensionB2AAA1HB3AAAA1Z,
                this,
                id
        );
        return dim;
    }

    Actor *Level::getNearestDimensionPlayer(const BlockPos &pos, int dimID) {
        Actor *nearest = nullptr;
        float minDistance = 512;
        this->forEachPlayer([&nearest, &pos, &dimID, &minDistance](Actor *player) {
            if (player->getDimensionID() == dimID) {
                BlockPos p = player->getPos()->toBlockPos();
                auto d = p.distanceTo(pos);
                if (d < minDistance) {
                    minDistance = d;
                    nearest = player;
                }
            }
        });
        return nearest;
    }
}
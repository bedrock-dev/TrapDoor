//
// Created by xhy on 2020/10/29.
//

#include "Level.h"

#include "Block.h"
#include "Dimension.h"
#include "Offset.h"
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    using namespace SymHook;

    void Level::forEachPlayer(const std::function<void(Actor *)> &todo) {
        auto f = [&](Actor &actor) {
            todo(&actor);
            return true;
        };
        this->newForEachPlayer(f);
    }

    void Level::newForEachPlayer(std::function<bool(Actor &)> todo) {
        SYM_CALL(void (*)(Level *, std::function<bool(Actor &)>),
                 Level_forEachPlayer_71a4f564, this, todo);
    }

    Actor *Level::getNearestPlayer(BlockPos &pos) {
        Actor *nearest = nullptr;
        float minDistance = 512;
        this->forEachPlayer([&pos, &minDistance, &nearest](Actor *player) {
            BlockPos p(player->getPos()->x, player->getPos()->y,
                       player->getPos()->z);
            auto d = p.distanceTo(pos);
            if (d < minDistance) {
                minDistance = d;
                nearest = player;
            }
        });
        return nearest;
    }

    Dimension *Level::getDimFromID(int id) {
        return SYM_CALL(Dimension * (*)(Level *, int),
                        Level_getDimension_6fab9459, this, id);
    }

    Actor *Level::getNearestDimensionPlayer(const BlockPos &pos, int dimID) {
        Actor *nearest = nullptr;
        float minDistance = 512;
        this->forEachPlayer(
            [&nearest, &pos, &dimID, &minDistance](Actor *player) {
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

}  // namespace trapdoor

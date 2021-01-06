//
// Created by xhy on 2021/1/3.
//
#include "entity/Actor.h"
#include "graphics/Graphics.h"
#include "PlayerFunction.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "graphics/BlockPos.h"
#include "graphics/Particle.h"

namespace mod {
    void PlayerFunction::tick() {
        if (gameTick % 15 == 0) {
            auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
            modInstance->getLevel()->forEachPlayer([&](trapdoor::Actor *player) {
                if (this->enables[player->getNameTag()]) {
                    drawChunkBound(player);
                }
                //add other functions here
            });
        }
        this->gameTick = (this->gameTick + 1) % 15;
    }

    void PlayerFunction::drawChunkBound(trapdoor::Actor *player) {
        int dimensionID = player->getDimensionID();
        auto playerPos = player->getPos()->toBlockPos();
        auto p = playerPos.toChunkPos();
        trapdoor::spawnChunkSurfaceParticle(p, dimensionID);
    }
}


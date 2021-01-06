//
// Created by xhy on 2021/1/5.
//

#include "SlimeChunkHelper.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "Particle.h"

namespace mod {
    void SlimeChunkHelper::tick() {
        if (!this->enable)return;
        if (gameTick % 2000 == 0) {
            this->updateChunkPosList();
            this->draw();
        }
        this->gameTick = (this->gameTick + 1) % 2000;
    }

    void SlimeChunkHelper::updateChunkPosList() {
        if (!this->enable)return;
        this->posList.clear();
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        modInstance->getLevel()->forEachPlayer([&](trapdoor::Actor *player) {
                                                   if (player->getDimensionID() == 0) { //遍历主世界玩家
                                                       int num = 0;
                                                       auto playerChunkPos = player->getPos()->toBlockPos().toChunkPos();
                                                       auto pos = playerChunkPos;
                                                       for (int i = -showRadius; i < showRadius; i++) {
                                                           for (int j = -showRadius; j < showRadius; j++) {
                                                               pos.x = playerChunkPos.x + i;
                                                               pos.z = playerChunkPos.z + j;
                                                               if (pos.isSlimeChunk()) {
                                                                   ++num;
                                                                   this->posList.insert(pos);
                                                               }
                                                           }
                                                       }
                                                   }
                                               }
        );
    }

    void SlimeChunkHelper::draw() {
        for (const auto i:this->posList)
            trapdoor::spawnSlimeChunkParticle(i);
    }

    void SlimeChunkHelper::setRadius(int r) {
        this->showRadius = r;
    }
}

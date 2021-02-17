//
// Created by xhy on 2021/1/5.
//

#include "SlimeChunkHelper.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "Particle.h"
#include "lib/Remotery.h"
namespace mod {
    void SlimeChunkHelper::tick() {
        rmt_ScopedCPUSample(SLIME, 0);
        constexpr int frequency = 100;
        if (!this->enable)return;
        if (gameTick % frequency == 0) {
            this->updateChunkPosList();
            this->draw();
        }
        this->gameTick = (this->gameTick + 1) % frequency;
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

    void SlimeChunkHelper::registerCommand(CommandManager &commandManager) {
        commandManager.registerCmd("slime", "command.slime.desc")
                ->then(ARG("show", "command.slime.show.desc", BOOL,
                           {
                               this->setAble(holder->getBool());
                               //    this->slimeChunkHelper.updateChunkPosList();
                               //   this->slimeChunkHelper.draw();
                               broadcastMsg("设置史莱姆区块显示为 %d",
                                            holder->getBool());
                           }))
                ->then(ARG("c", "command.slime.c.desc", NONE,
                           {
                               this->updateChunkPosList();
                               this->draw();
                               broadcastMsg("已经清除史莱姆区块缓存");
                           }))
                ->then(ARG("r", "command.slime.r.desc", INT, {
                    this->setRadius(holder->getInt());
                    this->updateChunkPosList();
                    this->draw();
                    broadcastMsg("已经清除史莱姆区块缓存");
                }));
    }
}

//
// Created by xhy on 2021/2/2.
//

#include "SelectRegion.h"

#include  "trapdoor.h"

namespace mod {
    void SelectRegion::tick(GRAPH_COLOR color) {
        if (gameTick % 40 == 0) {
            this->draw(color);
        }
        gameTick = (gameTick + 1) % 40;
    }

    void SelectRegion::setPos1(trapdoor::BlockPos &pos, trapdoor::Actor *player) {
        int d = player->getDimensionID();
        if (hasSetPos2 && this->dim != d) {
            trapdoor::warning(player, "两点维度不一致，选点取消");
            return;
        }
        this->hasSetPos1 = true;
        this->boundingBox.minPos = pos;
        trapdoor::info(player, "设置点1 %d %d %d", pos.x, pos.y, pos.z);
        if (hasSetPos2)adjust();
    }

    void SelectRegion::setPos2(trapdoor::BlockPos &pos, trapdoor::Actor *player) {
        int d = player->getDimensionID();
        if (hasSetPos1 && this->dim != d) {
            trapdoor::warning(player, "两点维度不一致，选点取消");
            return;
        }
        this->hasSetPos2 = true;
        this->boundingBox.maxPos = pos;
        trapdoor::info(player, "设置点2 %d %d %d", pos.x, pos.y, pos.z);
        if (hasSetPos1)adjust();
    }

    void SelectRegion::adjust() {
        auto p1 = boundingBox.minPos;
        auto p2 = boundingBox.maxPos;
        int minX = p1.x < p2.x ? p1.x : p2.x;
        int maxX = p1.x < p2.x ? p2.x : p1.x;
        int minY = p1.y < p2.y ? p1.y : p2.y;
        int maxY = p1.y < p2.y ? p2.y : p1.y;
        int minZ = p1.z < p2.z ? p1.z : p2.z;
        int maxZ = p1.z < p2.z ? p2.z : p1.z;
        boundingBox.minPos = {minX, minY, minZ};
        boundingBox.maxPos = {maxX, maxY, maxZ};
    }

    void SelectRegion::draw(GRAPH_COLOR color) {
        if (!this->hasSet() || !showOutLine)return;
        trapdoor::spawnRectangleParticle(this->boundingBox.toAABB(), color, this->dim);
    }


}

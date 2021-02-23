//
// Created by xhy on 2021/2/2.
//

#ifndef MOD_SELECTREGION_H
#define MOD_SELECTREGION_H

#include "trapdoor.h"

namespace mod {
    class SelectRegion {
        int dim = 0;
        bool showOutLine = true;
        size_t gameTick = 0;
        BoundingBox boundingBox;
        bool hasSetPos1 = false;
        bool hasSetPos2 = false;

        void adjust();

    public:
        void setPos1(trapdoor::BlockPos &pos, trapdoor::Actor *player);

        void setPos2(trapdoor::BlockPos &pos, trapdoor::Actor *player);

        inline BoundingBox getBoundingBox() const { return this->boundingBox; }

        void tick(GRAPH_COLOR color);

        void draw(GRAPH_COLOR color);

        inline bool hasSet() { return this->hasSetPos2 && this->hasSetPos2; }

        void forceSetBoundingBox(BoundingBox box) {
            this->boundingBox = box;
            this->hasSetPos1 = true;
            this->hasSetPos2 = true;
        }
    };
}

#endif //MOD_SELECTREGION_H

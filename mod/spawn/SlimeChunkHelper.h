//
// Created by xhy on 2021/1/5.
//

#ifndef MOD_SLIMECHUNKHELPER_H
#define MOD_SLIMECHUNKHELPER_H

#include <set>

#include "commands/CommandManager.h"
#include "graphics/BlockPos.h"
#include "tools/noncopyable .h"
#include "trapdoor.h"

namespace mod {

    class SlimeChunkHelper : noncopyable {
        int showRadius = 5;
        bool enable = false;
        size_t gameTick = 0;
        std::set<trapdoor::ChunkPos> posList;

       public:
        inline void setAble(bool able) { this->enable = able; }

        void updateChunkPosList();

        void tick();

        void setRadius(int r);

        void registerCommand(trapdoor::CommandManager &manager);

        void draw();
    };
}  // namespace mod
#endif  // MOD_SLIMECHUNKHELPER_H

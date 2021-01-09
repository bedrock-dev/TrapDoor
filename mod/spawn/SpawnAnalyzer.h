//
// Created by xhy on 2021/1/1.
//

#ifndef MOD_SPAWNANALYZER_H
#define MOD_SPAWNANALYZER_H

#include <string>
#include "graphics/BlockPos.h"
#include "graphics/Vec3.h"
#include <map>
#include "entity/Actor.h"

namespace mod {
    class SpawnAnalyzer {
        bool inAnalyzing = false;
        size_t gameTick = 0;
    public:
    public:
        struct MobSpawnInfo {
            size_t tick = 0;
            std::string type; //类型
            trapdoor::Vec3 position; //位置
            bool isSurface; //是否露天
            bool success; //是否生成成功
        };

        void start(trapdoor::Actor *player);

        void end(trapdoor::Actor *player);

        inline bool isRunning() const { return this->inAnalyzing; }


        void addMobData(const SpawnAnalyzer::MobSpawnInfo &info);

        inline size_t getTick() const { return this->gameTick; }

        inline void clearData(trapdoor::Actor *player);

        inline void tick() { ++this->gameTick; }

        void printSimpleData(trapdoor::Actor *player, const std::string &typePatten = "null") const;

        void printSpeedGraph(trapdoor::Actor *player, size_t freq) const;

    private:
        std::vector<MobSpawnInfo> spawnData;
    };
}


#endif //MOD_SPAWNANALYZER_H

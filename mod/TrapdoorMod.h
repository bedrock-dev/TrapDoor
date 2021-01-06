//
// Created by xhy on 2020/12/23.
//

#ifndef MOD_TRAPDOORMOD_H
#define MOD_TRAPDOORMOD_H

#include "BDSMod.h"
#include "village/Village.h"
#include "hopper/HopperCounter.h"
#include "spawn/HsaManager.h"
#include "config/ConfigManager.h"
#include "spawn/SpawnHelper.h"
#include "spawn/SpawnAnalyzer.h"
#include "function/BlockRotationHelper.h"
#include "player/PlayerFunction.h"
#include "player/SimpleBuilder.h"
#include "SlimeChunkHelper.h"
#include "player/PlayerStatisticManager.h"

namespace mod {

    class TrapdoorMod : public trapdoor::BDSMod {
    private:
        HopperChannelManager hopperChannelManager;
        VillageHelper villageHelper;
        HsaManager hsaManager;
        ConfigManager configManager;
        SpawnHelper spawnHelper;
        SpawnAnalyzer spawnAnalyzer;
        BlockRotationHelper rotationHelper;
        PlayerFunction playerFunctions;
        SimpleBuilder simpleBuilder;
        SlimeChunkHelper slimeChunkHelper;
        PlayerStatisticManager playerStatisticManager;

        void registerTickCommand();

    public:
        static void printCopyRightInfo();

        void initialize();

        void registerCommands() override;

        void useOnHook(Actor *player, const std::string &itemName, BlockPos &pos, unsigned int facing,
                       const Vec3 &) override;

        void heavyTick();

        void lightTick();

        //get functions
        inline HopperChannelManager &getHopperChannelManager() { return this->hopperChannelManager; }

        inline VillageHelper &getVillageHelper() { return this->villageHelper; }

        inline HsaManager &getHsaManager() { return this->hsaManager; }

        inline SpawnAnalyzer &getSpawnAnalyzer() { return this->spawnAnalyzer; }

        inline PlayerStatisticManager &getPlayerStatisticManager() { return this->playerStatisticManager; }
    };
}

#endif //MOD_TRAPDOORMOD_H

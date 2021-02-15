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
#include "dirtyLitematica/SimpleLitematica.h"
#include "dirtyLitematica/SelectRegion.h"

namespace mod {

    struct ModInfo {
        const std::string minecraftVersion = "1.16.4.02";
        const std::string modVersion = "trapdoor-0.9.32";
    };

    struct SingleFunction {
        bool preventExplosion = false;
        bool preventNCUpdate = false;
        bool enableBetterMspt = false;
    };

    class TrapdoorMod : public trapdoor::BDSMod {
    private:
        SingleFunction singleFunctions;
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

        SimpleLitematica simpleLitematica;

        void initFunctionEnable();

        void registerDevCommand();


    public:
        ModInfo modeInfo;


    public:
        static void printCopyRightInfo();

        static void printOSInfo(trapdoor::Actor *player);

        void initialize() override;

        void registerCommands() override;

        void useOnHook(Actor *player, const std::string &itemName, BlockPos &pos, unsigned int facing,
                       const Vec3 &) override;


        CommandPermissionLevel
        resetVanillaCommandLevel(const std::string &name, CommandPermissionLevel oldLevel) override;

        void heavyTick();

        void lightTick();

        inline bool readConfigFile(const std::string &configFileName) {
            return this->configManager.initialize(configFileName);
        }

        bool attackEntityHook(Actor *entity1, Actor *entity2) override;

        //get functions
        inline HopperChannelManager &getHopperChannelManager() { return this->hopperChannelManager; }

        inline VillageHelper &getVillageHelper() { return this->villageHelper; }

        inline HsaManager &getHsaManager() { return this->hsaManager; }

        inline SpawnAnalyzer &getSpawnAnalyzer() { return this->spawnAnalyzer; }

        inline PlayerStatisticManager &getPlayerStatisticManager() { return this->playerStatisticManager; }

        inline std::string getLevelName() { return this->configManager.getServerConfig().levelName; }

        inline SingleFunction getSingFunction() { return this->singleFunctions; }

    };
}

#endif //MOD_TRAPDOORMOD_H
//
// Created by xhy on 2020/12/23.
//

#ifndef MOD_TRAPDOORMOD_H
#define MOD_TRAPDOORMOD_H

#include "BDSMod.h"
#include "SlimeChunkHelper.h"
#include "config/ConfigManager.h"
#include "function/BlockRotationHelper.h"
#include "function/HopperCounter.h"
#include "function/SimpleBuilder.h"
#include "player/PlayerFunction.h"
#include "spawn/HsaManager.h"
#include "spawn/SpawnHelper.h"
#include "village/Village.h"
//#include "dirtyLitematica/SimpleLitematica.h"
//#include "dirtyLitematica/SelectRegion.h"
#include "fakePlayer/FakePlayerClient.h"

namespace mod {

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
        BlockRotationHelper rotationHelper;
        PlayerFunction playerFunctions;
        SimpleBuilder simpleBuilder;
        SlimeChunkHelper slimeChunkHelper;
        FakePlayerClient *fakePlayerClient = nullptr;

        void initFunctionEnable();

       public:
        static void printCopyRightInfo();

        static std::string getModVersion();

        static void printOSInfo(trapdoor::Actor *player);

        void initialize() override;

        void registerCommands() override;

        void useOnHook(Actor *player, const std::string &itemName,
                       BlockPos &pos, unsigned int facing,
                       const Vec3 &) override;

        CommandPermissionLevel resetVanillaCommandLevel(
            const std::string &name, CommandPermissionLevel oldLevel) override;

        void heavyTick();

        void lightTick();

        inline bool readConfigFile(const std::string &configFileName) {
            return this->configManager.initialize(configFileName);
        }

        bool attackEntityHook(Actor *entity1, Actor *entity2) override;

        // get functions
        inline HopperChannelManager &getHopperChannelManager() {
            return this->hopperChannelManager;
        }

        inline VillageHelper &getVillageHelper() { return this->villageHelper; }

        inline HsaManager &getHsaManager() { return this->hsaManager; }

        inline SimpleBuilder &getSimpleBuilder() { return this->simpleBuilder; }

        inline std::string getLevelName() {
            return this->configManager.getServerConfig().levelName;
        }
        inline ConfigManager &getConfigManager() { return this->configManager; }

        inline SingleFunction &getSingFunction() {
            return this->singleFunctions;
        }
    };
}  // namespace mod

#endif  // MOD_TRAPDOORMOD_H
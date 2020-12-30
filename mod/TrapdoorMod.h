//
// Created by xhy on 2020/12/23.
//

#ifndef MOD_TRAPDOORMOD_H
#define MOD_TRAPDOORMOD_H

#include "BDSMod.h"
#include "village/Village.h"
#include "hopper/HopperCounter.h"
#include "spawn/HsaManager.h"

namespace mod {
    class TrapdoorMod : public trapdoor::BDSMod {
    private:
        HopperChannelManager hopperChannelManager;
        VillageHelper villageHelper;
        HsaManager hsaManager;

    public:
        void initialize();

        inline HopperChannelManager &getHopperChannelManager() { return this->hopperChannelManager; }

        inline VillageHelper &getVillageHelper() { return this->villageHelper; }

        inline HsaManager &getHsaManager() { return this->hsaManager; }

        void registerCommands() override;

        void registerTickCommand();

        static void printCopyRightInfo();

        void heavyTick();

        void lightTick();

    };

}


#endif //MOD_TRAPDOORMOD_H

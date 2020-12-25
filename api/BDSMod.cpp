//
// Created by xhy on 2020/8/25.
//

#include "BDSMod.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    //全局模组对象
    BDSMod *bdsMod = nullptr;

    void initializeMod(BDSMod *BDSMod) {
        L_INFO("create BDS mod instance");
        trapdoor::bdsMod = BDSMod;
        L_ERROR("error info");
//        L_INFO("info ");
//        L_ERROR("warning");
//        L_DEBUG("debug info");
    }

    Level *BDSMod::getLevel() {
        return this->serverLevel;
    }

    void BDSMod::setCommandRegistry(void *registry) {
        this->commandRegistry = registry;
    }

    void *BDSMod::getCommandRegistry() {
        return this->commandRegistry;
    }

    void BDSMod::setLevel(Level *level) {
        L_INFO("init server level");
        this->serverLevel = level;
    }

    CommandManager &BDSMod::getCommandManager() {
        return this->commandManager;
    }

    void BDSMod::registerCommands() {
        L_INFO("begin register command");
    }


}

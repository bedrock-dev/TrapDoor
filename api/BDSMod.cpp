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
        if (!this->commandRegistry) {
            L_ERROR("fail to register command!![commandRegistry is null ptr]");
        }
        L_INFO("begin register command");
        getCommandManager().registerCmd("apicfg")
                ->then(ARG("pvd", "设置例子可见距离", INT, {
                    this->getCfg().particleViewDistance = holder->getInt();
                }))
                ->then(ARG("pm", "牺牲一定显示效果减少显示卡顿", BOOL, {
                    this->getCfg().particlePerformanceMode = holder->getBool();
                }));
    }

    std::map<std::string, PlayerBuffer> &BDSMod::getPlayerBuffer() {
        return this->playerCache;
    }


}

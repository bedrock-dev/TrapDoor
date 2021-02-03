//
// Created by xhy on 2020/8/25.
//

#include "BDSMod.h"
#include "tools/DirtyLogger.h"
#include "SymHook.h"
#include "lib/mod.h"

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
        L_INFO("set commandRegistry");
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
        getCommandManager().registerCmd("apicfg", "部分设置")
                ->then(ARG("pvd", "设置粒子可见距离", INT, {
                    this->getCfg().particleViewDistance = holder->getInt();
                }))
                ->then(ARG("pm", "牺牲一定显示效果减少部分显示卡顿", BOOL, {
                    this->getCfg().particlePerformanceMode = holder->getBool();
                }));
    }

    std::map<std::string, PlayerBuffer> &BDSMod::getPlayerBuffer() {
        return this->playerCache;
    }

    void BDSMod::initialize() {
        L_INFO("==== trapdoor mod begin init ====");
        L_INFO("init thread pool");
        this->threadPool = new ThreadPool(std::thread::hardware_concurrency());
    }

    trapdoor::Actor *BDSMod::fetchEntity(int64_t id, bool b) {
        using namespace SymHook;
        return SYM_CALL(
                Actor * (*)(Level * ,
                int64_t, bool),
                MSSYM_B1QE11fetchEntityB1AA5LevelB2AAE13QEBAPEAVActorB2AAE14UActorUniqueIDB3AAUA1NB1AA1Z,
                this->getLevel(), id, b
        );
    }
}

//
// Created by xhy on 2020/8/25.
//

#include "BDSMod.h"
#include "tools/DirtyLogger.h"
#include "SymHook.h"
#include "lib/mod.h"
#include "tools/Message.h"

namespace trapdoor {
    //全局模组对象
    BDSMod *bdsMod = nullptr;

    void initializeMod(BDSMod *BDSMod) {
        L_DEBUG("create BDS mod instance");
        trapdoor::bdsMod = BDSMod;
    }

    Level *BDSMod::getLevel() {
        return this->serverLevel;
    }

    void BDSMod::setCommandRegistry(void *registry) {
        L_DEBUG("set commandRegistry");
        this->commandRegistry = registry;
    }

    void *BDSMod::getCommandRegistry() {
        return this->commandRegistry;
    }

    void BDSMod::setLevel(Level *level) {
        L_DEBUG("init server level");
        this->serverLevel = level;
    }

    CommandManager &BDSMod::getCommandManager() {
        return this->commandManager;
    }

    void BDSMod::registerCommands() {

        if (!this->commandRegistry) {
            L_ERROR("fail to register command!![commandRegistry is null ptr]");
        }
        L_DEBUG("begin register command");
        this->registerLangCommand();
        getCommandManager().registerCmd("apicfg", "command.apicfg.desc")
                ->then(ARG("pvd", "command.apicfg.pvd.desc", INT, {
                    this->getCfg().particleViewDistance = holder->getInt();
                }))
                ->then(ARG("pm", "command.apicfg.pm.desc", BOOL, {
                    this->getCfg().particlePerformanceMode = holder->getBool();
                }));
    }

    std::map<std::string, PlayerBuffer> &BDSMod::getPlayerBuffer() {
        return this->playerCache;
    }

    void BDSMod::initialize() {
        L_DEBUG("init thread pool");
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

    void BDSMod::registerLangCommand() {
        this->commandManager.registerCmd("lang", "command.lang.desc")
                ->then(ARG("list", "command.lang.list.desc", NONE, {
                    trapdoor::info(player, this->i18NManager.getAllLanguages());
                }))
                ->then(ARG("set", "command.lang.set.desc", STR, {
                    auto result = this->i18NManager.tryChangeLanguage(holder->getString());
                    if (result) {
                        info(player, LANG("command.lang.set.success"));
                    } else {
                        info(player, LANG("command.lang.set.failure"));
                    }
                }));
    }
}

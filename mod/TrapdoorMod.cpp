//
// Created by xhy on 2020/12/23.
//

#include "TrapdoorMod.h"

#include "VanillaBlockType.h"
#include "commands/Command.h"
#include "entity/Item.h"
#include "eval/Eval.h"
#include "function/BackupHelper.h"
#include "function/FunctionCommands.h"
#include "lib/Remotery.h"
#include "os/process_stat.h"
#include "test/TrapdoorTest.h"
#include "tick/GameTick.h"
#include "trapdoor.h"

namespace mod {

    void TrapdoorMod::heavyTick() {
        rmt_ScopedCPUSample(MOD_TICK, 0);
        this->villageHelper.tick();
        this->hsaManager.tick();
        this->spawnHelper.tick();

        this->playerFunctions.tick();
        this->slimeChunkHelper.tick();
        if (this->fakePlayerClient) this->fakePlayerClient->tick();
    }

    void TrapdoorMod::lightTick() {
        this->tick();
        this->hopperChannelManager.tick();
        //   this->spawnAnalyzer.tick();
    }

    //这个函数会在初始化Level对象后执行
    void TrapdoorMod::initialize() {
        L_DEBUG("mod init");
        BDSMod::initialize();
        this->commandManager.setCommandConfig(
            this->configManager.getCommandsConfig());
        mod::initBackup();
        this->villageHelper.setConfig(this->configManager.getVillageConfig());
        getCurProcessCPUUsage();
        this->initFunctionEnable();
        initBlockMap();
        InitItemNameMap();
        //初始化假人客户端的线程池
        this->fakePlayerClient = new FakePlayerClient(this->getThreadPool());
        this->fakePlayerClient->registerFakePlayerCommand(commandManager);
        L_INFO("[INFO] Trapdoor init finish,Server Start");
    }

    void TrapdoorMod::registerCommands() {
        using namespace trapdoor;
        BDSMod::registerCommands();
        tick::registerTickCommand(this->commandManager);
        tick::registerProfileCommand(this->commandManager);
        mod::test::registerTestCommand(this->commandManager);
        mod::registerBackupCommand(this->commandManager);
        this->hsaManager.registerCommand(this->commandManager);
        this->simpleBuilder.registerDrawCommand(this->commandManager);
        // this->simpleLitematica.registerCommand(this->commandManager);
        this->villageHelper.registerCommand(this->commandManager);
        this->hopperChannelManager.registerCommand(this->commandManager);
        registerGamemodeSwitchCommand(this->commandManager);
        this->slimeChunkHelper.registerCommand(this->commandManager);
        //功能开关命令
        commandManager.registerCmd("func", "command.func.desc")
            ->then(ARG("hopper", "command.func.hopper.desc", BOOL,
                       {
                           this->hopperChannelManager.setAble(
                               holder->getBool());
                           info(player, LANG("command.func.hopper.set"),
                                holder->getBool());
                       }))
            ->then(ARG("spawn", "command.func.spawn.desc", BOOL,
                       {
                           this->spawnHelper.setAble(holder->getBool());
                           info(player, LANG("command.func.spawn.set"),
                                holder->getBool());
                       }))
            ->then(ARG("rotate", "command.func.rotate.desc", BOOL,
                       {
                           this->rotationHelper.setAble(holder->getBool());
                           info(player, LANG("command.func.rotate.set"),
                                holder->getBool());
                       }))
            ->then(ARG("draw", "command.func.draw.desc", BOOL,
                       {
                           this->simpleBuilder.setAble(holder->getBool());
                           info(player, LANG("command.func.draw.set"),
                                holder->getBool());
                       }))

            ->then(ARG("expl", "command.func.expl.desc", BOOL,
                       {
                           this->singleFunctions.preventExplosion =
                               holder->getBool();
                           info(player, LANG("command.func.expl.set"),
                                holder->getBool());
                       }))

            ->then(ARG("ncud", "command.func.ncud.desc", BOOL, {
                // FUNC_DISABLED(player)
                this->singleFunctions.preventNCUpdate = holder->getBool();
                info(player, LANG("command.func.ncud.set"), holder->getBool());
            }));

        commandManager.registerCmd("self", "command.self.desc")
            ->then(ARG(
                "chunk", "command.self.chunk.desc", BOOL,
                {
                    if (!configManager.getSelfEnableConfig().enableChunkShow) {
                        error(player, LANG("command.error.config"));
                        return;
                    }
                    this->playerFunctions.setShowChunkAble(player->getNameTag(),
                                                           holder->getBool());
                    info(player, LANG("command.self.chunk.set"),
                         holder->getBool());
                }))
            ->then(ARG("me", "command.self.me.desc", BOOL,
                       {
                           if (!configManager.getSelfEnableConfig()
                                    .enableDistanceMeasure) {
                               error(player, LANG("command.error.config"));
                               return;
                           }
                           this->playerFunctions
                               .getMeasureData(player->getNameTag())
                               .enableMeasure = holder->getBool();
                           info(player, LANG("command.self.me.set"),
                                holder->getBool());
                       }))
            ->then(ARG("rs", "command.self.rs.desc", BOOL,
                       {
                           FUNC_DISABLED(player)
                           return;
                           if (!configManager.getSelfEnableConfig()
                                    .enableRedstoneStick) {
                               error(player, LANG("command.error.config"));
                               return;
                           }
                           this->playerFunctions.setRedstoneHelperAble(
                               player->getNameTag(), holder->getBool());
                           info(player, LANG("command.self.rs.set"),
                                holder->getBool());
                       }))
            ->EXE({ PlayerFunction::printDebugInfo(player); });

        commandManager.registerCmd("here", "command.here.desc")->EXE({
            PlayerFunction::broadcastSimpleInfo(player);
        });
        commandManager.registerCmd("l", "command.l.desc")->EXE({
            PlayerFunction::listAllPlayers(player);
        });
        commandManager.registerCmd("os", "command.os.desc")->EXE({
            TrapdoorMod::printOSInfo(player);
        });
        commandManager.registerCmd("cl", "command.cl.desc", Any, ArgType::STR)
            ->EXE({ mod::eval(player, holder->getString()); });
        commandManager.registerCmd("td?", "command.td?.desc")->EXE({
            this->commandManager.printfHelpInfo(player);
        });
    }

    void TrapdoorMod::printCopyRightInfo() {
        const char *banner =
            "\n"
            "  _______                  _                   \n"
            " |__   __|                | |                  \n"
            "    | |_ __ __ _ _ __   __| | ___   ___  _ __  \n"
            "    | | '__/ _` | '_ \\ / _` |/ _ \\ / _ \\| '__| \n"
            "    | | | | (_| | |_) | (_| | (_) | (_) | |    \n"
            "    |_|_|  \\__,_| .__/ \\__,_|\\___/ \\___/|_|    \n"
            "                | |                            \n"
            "                |_|                            ";
        printf(
            "%s\n  "
            "\ngithub:https://github.com/hhhxiao/TrapDoor\nLicense: GPL\n",
            banner);
        printf("trapdoor version: %s\n", getModVersion().c_str());
        printf(
            "build time:     %s      "
            "%s\n-----------------------------------------------\n",
            __DATE__, __TIME__);
        fflush(stdout);
    }

    void TrapdoorMod::useOnHook(Actor *player, const std::string &itemName,
                                BlockPos &pos, unsigned int facing,
                                const Vec3 &v) {
        L_DEBUG("%.2f %.2f %.2f %s", v.x, v.y, v.z, itemName.c_str());
        //取消注释这一行可以看到右击地面的是什么东西
        if (itemName == "Bone" && this->spawnHelper.isEnable()) {
            spawnHelper.updateVerticalSpawnPositions(pos, player);
        } else if (itemName == "Gunpowder") {
            this->spawnHelper.printSpawnProbability(player, pos, 0);
        } else if (itemName == "Leather") {
            this->spawnHelper.printSpawnProbability(player, pos, 15);
        } else if (itemName == "Cactus") {
            this->hopperChannelManager.quickPrintData(player, pos);
            this->rotationHelper.rotate(pos, player->getBlockSource());
        } else if (itemName == "Wooden Sword") {
            this->playerFunctions.getMeasureData(player->getNameTag())
                .setPosition1(pos, player);
            //  this->simpleLitematica.getSelectRegion().setPos1(pos, player);
        } else if (itemName == "Stone Sword") {
            this->playerFunctions.getMeasureData(player->getNameTag())
                .setPosition2(pos, player);
            // this->simpleLitematica.getSelectRegion().setPos2(pos, player);
        } else if (itemName == "Stick") {
            this->playerFunctions.printRedstoneInfo(player, pos);
        }
    }

    CommandPermissionLevel TrapdoorMod::resetVanillaCommandLevel(
        const std::string &name, CommandPermissionLevel oldLevel) {
        auto lowLevelConfig = this->configManager.getLowLevelCommands();
        if (lowLevelConfig.find(name) != lowLevelConfig.end()) {
            L_DEBUG("set command %s level to gameMaster", name.c_str());
            return CommandPermissionLevel::GameMasters;
        } else {
            return oldLevel;
        }
    }

    void TrapdoorMod::printOSInfo(trapdoor::Actor *player) {
        printfSysInfo(player);
    }

    /*
     * 实体攻击接口
    @ return 返回false会阻止掉血,返回true会正常掉血
     @ entity1 进行攻击的实体
     @entity2 被攻击的实体
    */
    bool TrapdoorMod::attackEntityHook(Actor *entity1, Actor *entity2) {
        if (entity1->getActorId() != "player")
            return true;  //非玩家攻击直接忽略
        //开了居民村庄中心显示
        if (villageHelper.getShowDwellerStatus() &&
            (entity2->getActorId() == "iron_golem" ||
             entity2->getActorId() == "villager_v2")) {
            villageHelper.printDwellerInfo(entity1, entity2);
            return false;
        } else {
            return true;
        }
    }

    void TrapdoorMod::initFunctionEnable() {
        auto functionCfg = this->configManager.getFunctionConfig();
        this->spawnHelper.setAble(functionCfg.spawnHelper);
        this->rotationHelper.setAble(functionCfg.cactusRotation);
        this->simpleBuilder.setAble(functionCfg.simpleDraw);
        this->hopperChannelManager.setAble(functionCfg.hopperCounter);
    }

    std::string TrapdoorMod::getModVersion() {
#ifdef TD_VERSION
        const char *modVersion = TD_VERSION;
#else
        const char *modVersion = "unknown_mod_version";
#endif
#ifdef MC_VERSION
        const char *gameVersion = MC_VERSION;
#else
        const char *gameVersion = "unknown_mcbe_version";
#endif
        std::string version =
            "TrapDoor-" + std::string(modVersion) + "-" + gameVersion;
#ifdef BETA
        version += "-test";
#endif
        return version;
    }
}  // namespace mod
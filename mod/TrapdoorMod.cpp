//
// Created by xhy on 2020/12/23.
//

#include "TrapdoorMod.h"
#include "commands/CommandManager.h"
#include "commands/Command.h"
#include "tick/GameTick.h"
#include "tools/DirtyLogger.h"
#include "tick/ActorProfiler.h"
#include "block/BlockSource.h"
#include "graphics/BlockPos.h"
#include "player/PlayerFunction.h"
#include "player/PlayerStatisticManager.h"
#include "function/BackupHelper.h"
#include "os/process_stat.h"
#include "tools/MsgBuilder.h"
#include "block/Block.h"
#include "eval/Eval.h"
#include "trapdoor.h"
#include "block/BlockLegacy.h"
#include "VanillaBlockType.h"

namespace mod {
    bool test(const trapdoor::BlockLegacy &l) {
        printf("qaq\n");
        return true;
    }

    void TrapdoorMod::heavyTick() {
        this->villageHelper.tick();
        this->hsaManager.tick();
        this->spawnHelper.tick();
        this->playerFunctions.tick();
        this->slimeChunkHelper.tick();
        this->simpleLitematica.tick();
    }

    void TrapdoorMod::lightTick() {
        this->hopperChannelManager.tick();
        //   this->spawnAnalyzer.tick();
    }

    //这个函数会在初始化Level对象后执行
    void TrapdoorMod::initialize() {
        BDSMod::initialize();
        this->commandManager.setCommandConfig(
                this->configManager.getCommandsConfig());
        this->playerStatisticManager.init("trapdoor.db");
        mod::initBackup();
        this->villageHelper.setConfig(this->configManager.getVillageConfig());
        get_cpu_usage();
        this->initFunctionEnable();
        initBlockMap();
        L_INFO("==== trapdoor init finish  ====\nServer Start");
    }

    void TrapdoorMod::registerCommands() {
        using namespace trapdoor;
        BDSMod::registerCommands();
        tick::registerTickCommand(this->commandManager);
        tick::registerProfileCommand(this->commandManager);
        mod::registerBackupCommand(this->commandManager);
        this->hsaManager.registerCommand(this->commandManager);
        this->simpleBuilder.registerDrawCommand(this->commandManager);
        this->simpleLitematica.registerCommand(this->commandManager);
        this->hopperChannelManager.registerCommand(this->commandManager);
        this->villageHelper.registerCommand(this->commandManager);
        this->hopperChannelManager.registerCommand(this->commandManager);
        this->registerDevCommand();
        //功能开关命令
        commandManager.registerCmd("func", "开启/关闭部分功能")
                ->then(
                        ARG("hopper", "开启/关闭漏斗计数器", BOOL,
                            {
                                this->hopperChannelManager.setAble(holder->getBool());
                                info(player, "设置漏斗计数器为 %d", holder->getBool());
                            }))
                ->then(ARG("spawn", "开启/关闭刷怪指示", BOOL,
                           {
                               this->spawnHelper.setAble(holder->getBool());
                               info(player, "设置刷怪指示器为 %d",
                                    holder->getBool());
                           }))

                ->then(ARG("rotate", "开启/关闭转方块", BOOL,
                           {
                               this->rotationHelper.setAble(holder->getBool());
                               info(player, "设置仙人掌转方块为 %d",
                                    holder->getBool());
                           }))
                ->then(ARG("draw", "开启/关闭draw命令", BOOL,
                           {
                               this->simpleBuilder.setAble(holder->getBool());
                               info(player, "设置简单建造为 %d", holder->getBool());
                           }))
                ->then(ARG(
                               "stat", "开启/关闭玩家行为统计", BOOL,
                               {
                                   this->playerStatisticManager.setAble(holder->getBool());
                                   info(player, "设置玩家行为统计为 %d", holder->getBool());
                               }))
                ->then(ARG(
                               "expl", "开启/关闭爆炸破坏地形", BOOL,
                               {
                                   this->singleFunctions.preventExplosion = holder->getBool();
                                   info(player, "设置爆炸破坏地形 %d", holder->getBool());
                               }))
                ->then(ARG("ncud", "开启/关闭阻止NE更新", BOOL, {
                    this->singleFunctions.preventNCUpdate = holder->getBool();
                    info(player, "设置阻止NC更新为 %d", holder->getBool());
                }));

        //史莱姆显示
        this->slimeChunkHelper.registerCommand(this->commandManager);
        //漏斗计数器

        //便捷模式切换
        commandManager.registerCmd("o", "切换到观察者模式")->EXE({
                                                             player->setGameMode(4);
                                                             broadcastMsg("设置玩家[%s]为观察者模式",
                                                                          player->getNameTag().c_str());
                                                         });

        commandManager.registerCmd("s", "切换到生存模式")->EXE({
                                                            player->setGameMode(0);
                                                            broadcastMsg("设置玩家[%s]为生存模式",
                                                                         player->getNameTag().c_str());
                                                        });

        commandManager.registerCmd("c", "切换到创造模式")->EXE({
                                                            player->setGameMode(1);
                                                            broadcastMsg("设置玩家[%s]为创造者模式",
                                                                         player->getNameTag().c_str());
                                                        });

        //村庄

        commandManager.registerCmd("td?", "显示帮助")->EXE({
                                                           this->commandManager.printfHelpInfo(player);
                                                       });
        commandManager.registerCmd("self", "玩家个人功能")
                ->then(ARG(
                               "chunk", "区块显示", BOOL,
                               {
                                   if (!configManager.getSelfEnableConfig().enableChunkShow) {
                                       error(player, "该功能已被关闭，请联系服主");
                                       return;
                                   }
                                   this->playerFunctions.setShowChunkAble(player->getNameTag(),
                                                                          holder->getBool());
                                   info(player, "设置你的区块显示为 %d", holder->getBool());
                               }))
                ->then(ARG(
                               "me", "测量", BOOL,
                               {
                                   if (!configManager.getSelfEnableConfig()
                                           .enableDistanceMeasure) {
                                       error(player, "该功能已被关闭，请联系服主");
                                       return;
                                   }
                                   this->playerFunctions.getMeasureData(player->getNameTag())
                                           .enableMeasure = holder->getBool();
                                   info(player, "设置你的测量为 %d", holder->getBool());
                               }))
                ->then(ARG("rs", "信号源显示", BOOL,
                           {
                               if (!configManager.getSelfEnableConfig()
                                       .enableRedstoneStick) {
                                   error(player, "该功能已被关闭，请联系服主");
                                   return;
                               }
                               this->playerFunctions.setRedstoneHelperAble(
                                       player->getNameTag(), holder->getBool());
                               info(player, "设置你的信号源提示为 %d",
                                    holder->getBool());
                           }))
                ->EXE({ PlayerFunction::printDebugInfo(player); });

        commandManager.registerCmd("here", "广播自己的位置")->EXE({ PlayerFunction::broadcastSimpleInfo(player); });
        commandManager.registerCmd("l", "列出所有玩家坐标")->EXE({ PlayerFunction::listAllPlayers(player); });
        commandManager.registerCmd("os", "显示服务器信息")->EXE({ TrapdoorMod::printOSInfo(player); });
        commandManager.registerCmd("cl", "计算器", Any, ArgType::STR)->EXE({ mod::eval(player, holder->getString()); });
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
        printf(
                "build time:     %s      "
                "%s\n-----------------------------------------------\n",
                __DATE__, __TIME__);
        fflush(stdout);
    }


    void TrapdoorMod::useOnHook(Actor *player,
                                const std::string &itemName,
                                BlockPos &pos,
                                unsigned int facing,
                                const Vec3 &v) {
        //     L_INFO("%.2f %.2f %.2f", v.x,v.y,v.z , itemName.c_str());
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
            const std::string &name,
            CommandPermissionLevel oldLevel) {
        auto lowLevelConfig = this->configManager.getLowLevelCommands();
        if (lowLevelConfig.find(name) != lowLevelConfig.end()) {
            L_INFO("set command %s level to gameMaster", name.c_str());
            return CommandPermissionLevel::GameMasters;
        } else {
            return oldLevel;
        }
    }


    void TrapdoorMod::printOSInfo(trapdoor::Actor *player) {
        int CPUUsage = get_cpu_usage();
        uint64_t memory, virtualMemory, ioRead, ioWrite;
        get_memory_usage(&memory, &virtualMemory);
        get_io_bytes(&ioRead, &ioWrite);
        trapdoor::MessageBuilder builder;
        builder.text("CPU ")
                .num(CPUUsage)
                .text("%%%%\n")
                .text("Mem  ")
                .num(memory >> 20u)
                .text(" MB  VMem:")
                .num(virtualMemory >> 20u)
                .text(" MB\n")
                .text("Read/Write: ")
                .num(ioRead >> 10u)
                .text("/")
                .num(ioWrite >> 10u)
                .text(" KB")
                .send(player);
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
        this->playerStatisticManager.setAble(functionCfg.playerStat);
        this->simpleBuilder.setAble(functionCfg.simpleDraw);
        this->hopperChannelManager.setAble(functionCfg.hopperCounter);
    }


    void TrapdoorMod::registerDevCommand() {
        this->commandManager.registerCmd("dev", "develop")
                ->then(ARG("echo", "test1", STR, {
                }));
    }
}  // namespace mod
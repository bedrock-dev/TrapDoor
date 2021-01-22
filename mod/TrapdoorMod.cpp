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

namespace mod {
    void TrapdoorMod::heavyTick() {

        this->villageHelper.tick();
        this->hsaManager.tick();
        this->spawnHelper.tick();
        this->playerFunctions.tick();
        this->slimeChunkHelper.tick();
    }

    void TrapdoorMod::lightTick() {
        this->hopperChannelManager.tick();
        this->spawnAnalyzer.tick();
    }

//这个函数会在初始化Level对象后执行
    void TrapdoorMod::initialize() {
        BDSMod::initialize();
        this->commandManager.setCommandConfig(this->configManager.getCommandsConfig());
        this->playerStatisticManager.init("trapdoor.db");
        mod::initBackup();
        this->villageHelper.setConfig(this->configManager.getVillageConfig());
        get_cpu_usage();
        L_INFO("==== trapdoor init finish  ====\n Server Start");
    }

    void TrapdoorMod::registerCommands() {
        using namespace trapdoor;
        BDSMod::registerCommands();
        //tick
        this->registerTickCommand();
        //性能分析
        commandManager.registerCmd("prof", "游戏性能分析")
                ->then(ARG("actor", "实体更新性能分析", NONE, {
                    tick::profileEntities(player);
                }))
                ->EXE({ tick::profileWorld(player); });
        commandManager.registerCmd("mspt", "展示MSPT和TPS")->EXE({ tick::mspt(); });
//功能开关命令
        commandManager.registerCmd("func", "开启/关闭部分功能")
                ->then(ARG("hopper", "开启/关闭漏斗计数器", BOOL, {
                    if (!this->configManager.getFunctionConfig().hopperCounter) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->hopperChannelManager.setAble(holder->getBool());
                    info(player, "设置漏斗计数器为 %d", holder->getBool());
                }))
                ->then(ARG("spawn", "开启/关闭刷怪指示", BOOL, {
                    if (!this->configManager.getFunctionConfig().spawnHelper) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->spawnHelper.setAble(holder->getBool());
                    info(player, "设置刷怪指示器为 %d", holder->getBool());
                }))
                ->then(ARG("rotate", "开启/关闭转方块", BOOL, {
                    if (!configManager.getFunctionConfig().cactusRotation) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->rotationHelper.setAble(holder->getBool());
                    info(player, "设置仙人掌转方块为 %d", holder->getBool());
                }))
                ->then(ARG("draw", "开启/关闭区块draw命令", BOOL, {
                    if (!configManager.getFunctionConfig().simpleDraw) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->simpleBuilder.setAble(holder->getBool());
                    info(player, "设置简单建造为 %d", holder->getBool());
                }))
                ->then(ARG("stat", "开启/关闭玩家行为统计", BOOL, {
                    if (!configManager.getFunctionConfig().playerStat) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->playerStatisticManager.setAble(holder->getBool());
                    info(player, "设置玩家行为统计为 %d", holder->getBool());
                }));

        //史莱姆显示
        commandManager.registerCmd("slime", "史莱姆区块相关")
                ->then(ARG("show", "显示史莱姆区块", BOOL, {
                    this->slimeChunkHelper.setAble(holder->getBool());
                    //    this->slimeChunkHelper.updateChunkPosList();
                    //   this->slimeChunkHelper.draw();
                    broadcastMsg("设置史莱姆区块显示为 %d", holder->getBool());
                }))
                ->then(ARG("c", "清除缓存并重新绘制", NONE, {
                    this->slimeChunkHelper.updateChunkPosList();
                    this->slimeChunkHelper.draw();
                    broadcastMsg("已经清除史莱姆区块缓存");
                }))
                ->then(ARG("r", "设置显示半径", INT, {
                    this->slimeChunkHelper.setRadius(holder->getInt());
                    this->slimeChunkHelper.updateChunkPosList();
                    this->slimeChunkHelper.draw();
                    broadcastMsg("已经清除史莱姆区块缓存");
                }));
//漏斗计数器
        commandManager.registerCmd("counter", "漏斗计数器相关功能")
                ->then(Arg("r", "重置频道 [num]", ArgType::INT)->execute([this](ArgHolder *holder, Actor *player) {
                    this->hopperChannelManager.resetChannel(player, holder->getInt());
                }))
                ->then(Arg("p", "打印频道信息 [num]", ArgType::INT)->execute([this](ArgHolder *holder, Actor *player) {
                    this->hopperChannelManager.printChannel(player, holder->getInt());
                }));

//便捷模式切换
        commandManager.registerCmd("o", "切换到观察者模式")
                ->EXE({
                          player->setGameMode(4);
                          broadcastMsg("设置玩家[%s]为观察者模式", player->getNameTag().c_str());
                      });

        commandManager.registerCmd("s", "切换到生存模式")
                ->EXE({
                          player->setGameMode(0);
                          broadcastMsg("设置玩家[%s]为生存模式", player->getNameTag().c_str());
                      });

        commandManager.registerCmd("c", "切换到创造模式")
                ->EXE({
                          player->setGameMode(1);
                          broadcastMsg("设置玩家[%s]为创造者模式", player->getNameTag().c_str());
                      });

//村庄
        commandManager.registerCmd("village", "村庄相关功能")
                ->then(ARG("list", "显示所有正在加载的村庄", NONE, {
                    this->villageHelper.list(player);
                }))
                ->then(ARG("b", "显示村庄边框", BOOL, {
                    this->villageHelper.setShowBound(holder->getBool());
                    info(player, "设置村庄边框显示为 %d", holder->getBool());
                }))
                ->then(ARG("p", "显示POI查询范围", BOOL, {
                    this->villageHelper.setShowPOIRange(holder->getBool());
                    info(player, "设置村庄边框显示为 %d", holder->getBool());
                }))
                ->then(ARG("s", "显示铁傀儡刷新区域", BOOL, {
                    this->villageHelper.setShowGolemSpawnArea(holder->getBool());
                    info(player, "设置村庄边框显示为 %d", holder->getBool());
                }))
                ->then(ARG("c", "显示村庄中心", BOOL, {
                    this->villageHelper.setShowVillageCenter(holder->getBool());
                    info(player, "设置村庄边框显示为 %d", holder->getBool());
                }))
                ->then(ARG("v", "显示村民信息", BOOL, {
                    this->villageHelper.setShowDwellerStatus(holder->getBool());
                    info(player, "设置显示村民信息为 %d", holder->getBool());
                }))
                ->then(ARG("n", "显示最近村庄的详细信息", NONE, {
                    this->villageHelper.printNearestVillageInfo(player, *player->getPos());
                }))

                ->then(ARG("test", "???", NONE, {
                    trapdoor::warning(player, "you are not developer");
                    //   this->villageHelper.test();
                }));

        commandManager.registerCmd("td?", "显示帮助")
                ->EXE({
                          this->commandManager.printfHelpInfo(player);
                      });
        commandManager.registerCmd("hsa", "hsa显示相关")
                ->then(ARG("clear", "清空hsa缓存", NONE, {
                    auto num = hsaManager.clear();
                    broadcastMsg("一共 %d 个hsa区域被清空", num);
                }))
                ->then(ARG("list", "列出目前所有的hsa", NONE, {
                    hsaManager.list(player);
                }))
                ->then(ARG("show", "开启hsa显示", BOOL, {
                    hsaManager.setAble(holder->getBool());
                    info(player, "设置HSA显示为 %d", holder->getBool());
                }))
                ->then(ARG("find", "find the best pos", NONE,
                           {
                               broadcastMsg("find %s", hsaManager.findB(player).toString().c_str());
                           }))
                ->then(ARG("draw", "draw hsa", NONE, { hsaManager.draw(player); }));


        commandManager.registerCmd("draw", "简单建造")
                ->then(ARG("ci", "画圆", INT,
                           {
                               auto radius = holder->getInt();
                               bool hollow = holder->getInt() < 0;
                               if (radius < 0)
                                   radius = -radius;
                               this->simpleBuilder.buildCircle(player, radius,
                                                               hollow);
                           }))
                ->then(ARG("sp", "画球体", INT, {
                    auto radius = holder->getInt();
                    bool hollow = holder->getInt() < 0;
                    if (radius < 0)
                        radius = -radius;
                    this->simpleBuilder.buildSphere(player, radius, hollow);
                }))
                ->then(ARG("mr", "设置最大半径", INT, {
                    auto radius = holder->getInt();
                    if (radius < 0) {
                        error(player, "参数不合法(必须>=1)");
                    } else {
                        this->simpleBuilder.setMaxRadius(radius);
                    }
                }));


        commandManager.registerCmd("backup", "备份相关功能")
                ->then(ARG("b", "创建备份", NONE, {
                    mod::backup(player);
                }))
                ->then(ARG("l", "列出(最新的)备份", NONE, {
                    mod::listAllBackups(player);
                }))
                ->then(ARG("r", "恢复备份", INT, {
                    mod::restore(player, holder->getInt());
                }))
                ->then(ARG("crash", "崩服", NONE, {
                    //这种指令的存在真的好吗
                    *((char *) (0)) = 0;
                }));

        commandManager.registerCmd("self", "玩家个人功能")
                ->then(ARG("chunk", "区块显示", BOOL, {
                    if (!configManager.getSelfEnbaleConfig().enableChunkShow) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->playerFunctions.setShowChunkAble(player->getNameTag(), holder->getBool());
                    info(player, "设置你的区块显示为 %d", holder->getBool());
                }))
                ->then(ARG("me", "测量", BOOL, {
                    if (!configManager.getSelfEnbaleConfig().enableDistanceMeasure) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->playerFunctions.getMeasureData(player->getNameTag()).enableMeasure = holder->getBool();
                    info(player, "设置你的测量开启/关闭 %d", holder->getBool());
                }))
                ->then(ARG("rs", "测量", BOOL, {
                    if (!configManager.getSelfEnbaleConfig().enableRedstoneStick) {
                        error(player, "该功能已被关闭，请联系服主");
                        return;
                    }
                    this->playerFunctions.setRedstoneHelperAble(player->getNameTag(), holder->getBool());
                    info(player, "设置你的信号源提 示开启/关闭 %d", holder->getBool());
                }))

                ->EXE({ PlayerFunction::printInfo(player); });

        commandManager.registerCmd("os", "显示服务器信息")
                ->EXE({ TrapdoorMod::printOSInfo(player); });
    }

    void TrapdoorMod::registerTickCommand() {
        using namespace trapdoor;
        commandManager.registerCmd("tick", "改变世界运行状态")
                ->then(ARG("fz", "暂停世界运行", NONE, {
                    tick::freezeTick();
                }))
                ->then(ARG("slow", "放慢世界运行 [num] 倍速", INT, {
                    auto slowTime = holder->getInt();
                    if (slowTime > 1 && slowTime <= 64) {
                        tick::slowTick(slowTime);
                    } else {
                        error(player, "number must in [2-64]");
                    }
                }))
                ->then(ARG("acc", "加速世界运行[num]倍速", INT, {
                    auto wrapTime = holder->getInt();
                    if (wrapTime > 1 && wrapTime <= 10) {
                        tick::wrapTick(wrapTime);
                    } else {
                        error(player, "倍数必须在 [2-10] 之间");
                    }
                }))
                ->then(ARG("r", "重置世界运行", NONE, {
                    tick::resetTick();
                }))
                ->then(ARG("fw", "世界运行步进[num] gt", INT, {
                    tick::forwardTick(holder->getInt());
                }));

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
            this->rotationHelper.rotate(pos, player->getBlockSource());
        } else if (itemName == "Wooden Sword") {
            this->playerFunctions.getMeasureData(player->getNameTag()).setPosition1(pos, player);
        } else if (itemName == "Stone Sword") {
            this->playerFunctions.getMeasureData(player->getNameTag()).setPosition2(pos, player);
        } else if (itemName == "Stick") {
            this->playerFunctions.printRedstoneInfo(player, pos);
        }
    }


    CommandPermissionLevel
    TrapdoorMod::resetVanillaCommandLevel(const std::string &name, CommandPermissionLevel oldLevel) {
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
        builder.text("CPU ").num(CPUUsage).text("%%%%\n")
                .text("Mem  ").num(memory >> 20u).text(" MB  VMem:").num(virtualMemory >> 20u).text(" MB\n")
                .text("Read/Write: ").num(ioRead >> 10u).text("/").num(ioWrite >> 10u).text(" KB").send(player);
    }

    /*
     * 实体攻击接口
    @ return 返回false会阻止掉血,返回true会正常掉血
     @ entity1 进行攻击的实体
     @entity2 被攻击的实体
    */
    bool TrapdoorMod::attackEntityHook(Actor *entity1, Actor *entity2) {
        if (entity1->getActorId() != "player")return true;  //非玩家攻击直接忽略
        //开了居民村庄中心显示
        if (villageHelper.getShowDwellerStatus() &&
            (entity2->getActorId() == "iron_golem" || entity2->getActorId() == "villager_v2")) {
            villageHelper.printDwellerInfo(entity1, entity2);
            return false;
        } else {
            return true;
        }
    }
}

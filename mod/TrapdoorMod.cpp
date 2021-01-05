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
        this->configManager.initialize("trapdoor-config.json");
        this->commandManager.setCommandConfig(this->configManager.getCommandsConfig());
    }


    void TrapdoorMod::registerCommands() {
        using namespace trapdoor;
        BDSMod::registerCommands();


        this->registerTickCommand();
        commandManager.registerCmd("prof", "ticking profiling")
                ->then(ARG("actor", "显示详细的实体更新时间", NONE, {
                    tick::profileEntities(player);
                }))
                ->EXE({
                          tick::profileWorld(player);
                      });
        commandManager.registerCmd("mspt", "show mspt & tps")->EXE({ tick::mspt(); });
//功能开关命令
        commandManager.registerCmd("func", "开启/关闭部分功能")
                ->then(ARG("hc", "开启/关闭漏斗计数器", BOOL, {
                    this->hopperChannelManager.setAble(holder->getBool());
                    info(player, "设置漏斗计数器为 %d", holder->getBool());
                }))
                ->then(ARG("sh", "开启/关闭刷怪指示", BOOL, {
                    this->spawnHelper.setAble(holder->getBool());
                    info(player, "设置刷怪指示为 %d", holder->getBool());
                }))
                ->then(ARG("cr", "开启/关闭仙人掌转方块", BOOL, {
                    this->rotationHelper.setAble(holder->getBool());
                    info(player, "设置仙人掌转方块为 %d", holder->getBool());
                }))
                ->then(ARG("cs", "开启/关闭区块显示", BOOL, {
                    this->playerFunctions.setAble(player->getNameTag(), holder->getBool());
                    info(player, "设置你的区块显示为 %d", holder->getBool());
                }));

        commandManager.registerCmd("slime")
                ->then(ARG("show", "显示史莱姆区块", BOOL, {
                    this->slimeChunkHelper.setAble(holder->getBool());
                    this->slimeChunkHelper.updateChunkPosList();
                    this->slimeChunkHelper.draw();
                    broadcastMsg("已经开启史莱姆区块显示");
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
        commandManager.registerCmd("o", "switch to spectator mode")
                ->EXE({
                          player->setGameMode(3);
                          broadcastMsg("设置玩家[%s]为观察者模式", player->getNameTag().c_str());
                      });

        commandManager.registerCmd("s", "switch to survival mode")
                ->EXE({
                          player->setGameMode(0);
                          broadcastMsg("设置玩家[%s]为生存模式", player->getNameTag().c_str());
                      });

        commandManager.registerCmd("c", "switch to creative mode")
                ->EXE({
                          player->setGameMode(1);
                          broadcastMsg("设置玩家[%s]为创造者模式", player->getNameTag().c_str());
                      });


        commandManager.registerCmd("village", "村庄相关功能")
                ->then(ARG("list", "显示所有正在加载的村庄", NONE, {
                    this->villageHelper.list(player);
                }))
                ->then(ARG("show", "显示村庄边框和中心", BOOL, {
                    this->villageHelper.setVillageShowAble(holder->getBool());
                    info(player, "设置村庄显示为 %d", holder->getBool());
                }));

//        commandManager.registerCmd("cfg", "设置")
//                ->
//                        then(ARG("pvd", "config particle view distance(default=128)", INT, {
//                    particleViewDistance = holder->getInt();
//                    info(player, "set particle view distance to %d", particleViewDistance);
//                }));

        commandManager.registerCmd("td?", "显示帮助")
                ->EXE({
                          this->commandManager.printfHelpInfo(player);
                      });


        commandManager.registerCmd("dbg", "显示一些调试信息")
                ->EXE({ player->printInfo(); });

        commandManager.registerCmd("hsa", "hsa显示相关")
                ->then(ARG("clear", "清空hsa缓存", NONE, {
                    hsaManager.clear();
                    broadcastMsg("hsa缓存已经清空");
                }))
                ->then(ARG("list", "list nearest hsa", NONE, {
                    hsaManager.list(player);
                }))
                ->then(ARG("show", "show hsa", BOOL, {
                    hsaManager.setAble(holder->getBool());
                    info(player, "set hsa show to %d", holder->getBool());
                }));

        commandManager.registerCmd("spawncounter", "刷怪分析器")
                ->then(ARG("s", "开始统计", NONE, {
                    this->getSpawnAnalyzer().start(player);
                }))
                ->then(ARG("e", "结束统计", NONE, {
                    this->getSpawnAnalyzer().end(player);
                }))
                ->then(ARG("p", "打印数据", NONE, {
                    this->getSpawnAnalyzer().printSimpleData(player);
                }));

        commandManager.registerCmd("draw", "简单建造")
                ->then(ARG("ci", "画圆", INT, {
                    auto radius = holder->getInt();
                    bool hollow = holder->getInt() < 0;
                    if (radius < 0)radius = -radius;
                    this->simpleBuilder.buildCircle(player, radius, hollow);
                }))
                ->then(ARG("sp", "画圆", INT, {
                    auto radius = holder->getInt();
                    bool hollow = holder->getInt() < 0;
                    if (radius < 0)radius = -radius;
                    this->simpleBuilder.buildSphere(player, radius, hollow);
                }));
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
                        error(player, "number must in [2-10]");
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
        printf("build time:     %s      %s\n-----------------------------------------------\n", __DATE__, __TIME__);
        fflush(stdout);
    }


    void TrapdoorMod::useOnHook(Actor *player, const std::string &itemName, BlockPos &pos, unsigned int facing,
                                const Vec3 &) {
        //  L_DEBUG("%s", itemName.c_str());
        //取消注释这一行可以看到右击地面的是什么东西
        if (itemName == "Bone" && this->spawnHelper.isEnable()) {
            spawnHelper.updateVerticalSpawnPositions(pos, player);
        } else if (itemName == "Gunpowder") {
            this->spawnHelper.printSpawnProbability(player, pos, 0);
        } else if (itemName == "Leather") {
            this->spawnHelper.printSpawnProbability(player, pos, 15);
        } else if (itemName == "Cactus") {
            this->rotationHelper.rotate(pos, player->getBlockSource());
        }
    }

}

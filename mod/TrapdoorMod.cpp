//
// Created by xhy on 2020/12/23.
//

#include "TrapdoorMod.h"
#include "commands/CommandManager.h"
#include "commands/Command.h"
#include "tick/GameTick.h"
#include "tools/DirtyLogger.h"

namespace mod {
    void TrapdoorMod::heavyTick() {
        this->villageHelper.tick();
        this->hsaManager.tick();
    }

    void TrapdoorMod::lightTick() {
        this->hopperChannelManager.tick();
    }

    //这个函数会在初始化Level对象后执行
    void TrapdoorMod::initialize() {
        //todo
    }

    void TrapdoorMod::registerCommands() {
        using namespace trapdoor;
        BDSMod::registerCommands();
        if (!this->commandRegistry) {
            L_ERROR("fail to register command!![commandRegistry is null ptr]");
        }

        using namespace trapdoor;
        this->registerTickCommand();
        commandManager.registerCmd("prof", "ticking profiling")->EXE({ tick::profileWorld(player); });
        commandManager.registerCmd("mspt", "show mspt & tps", MEMBER)->EXE({ tick::mspt(); });
        //功能开关命令
        commandManager.registerCmd("func", "en/disable function")
                ->then(ARG("hc", "开启/关闭漏斗计数器", BOOL, {
                    this->hopperChannelManager.setAble(holder->getBool());
                    info(player, "set hoppercounter to %d", holder->getBool());
                }));
        //exp command

        //漏斗计数器
        commandManager.registerCmd("counter", "漏斗计数器相关功能", MEMBER)
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

        commandManager.registerCmd("s", "switch to survival mode", MEMBER)
                ->EXE({
                          player->setGameMode(0);
                          broadcastMsg("设置玩家[%s]为生存模式", player->getNameTag().c_str());
                      });

        commandManager.registerCmd("c", "switch to creative mode")
                ->EXE({
                          player->setGameMode(1);
                          broadcastMsg("设置玩家[%s]为创造者模式", player->getNameTag().c_str());
                      });


        commandManager.registerCmd("village", "村庄相关功能", MEMBER)
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

        commandManager.registerCmd("td?", "显示帮助", MEMBER)
                ->EXE({ this->commandManager.printfHelpInfo(player); });


        commandManager.registerCmd("dbg", "显示一些调试信息", MEMBER)
                ->EXE({ player->printInfo(); });


        commandManager.registerCmd("hsa", "show or list  nearset hsa")
                ->then(ARG("clear", "清空hsa缓存", NONE, {
                    hsaManager.clear();
                    broadcastMsg("hsa缓存已经清空");
                }))
                ->then(ARG("list", "list nearest hsa", NONE, {
                    hsaManager.list(player);
                }))
                ->then(ARG("show", "show hsa", BOOL, {
                    //enableHsaShow = holder->getBool();
                    // enableVillageShow = holder->getBool();
                    hsaManager.setAble(holder->getBool());
                    info(player, "set hsa show to %d", holder->getBool());
                }));
    }

    void TrapdoorMod::registerTickCommand() {
        using namespace trapdoor;
        commandManager.registerCmd("tick", "改变世界运行状态")
                ->then(ARG("fz", "暂停世界运行", NONE, { tick::freezeTick(); }))
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
                ->then(ARG("r", "重置世界运行", NONE, { tick::resetTick(); }))
                ->then(ARG("fw", "世界运行步进[num] gt", INT, { tick::forwardTick(holder->getInt()); }));

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


}

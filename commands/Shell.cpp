//
// Created by xhy on 2020/8/26.
//
#include "lib/mod.h"
#include "village/Village.h"
#include <map>
#include "spawn/Spawn.h"
#include <vector>
//#include "src/tick/Tick.h"
#include "tick/GameTick.h"
#include "Shell.h"
#include "entity/Actor.h"
#include "block/Hopper.h"
#include "lib/version.h"

using namespace SymHook;

void initCommand() {
    printf("init command...\n");
    getCommandManager().registerCmd("./a");
    getCommandManager().registerCmd("./tick")
            ->then(ARG("fz", NONE, { tick::freezeTick(); }))
            ->then(ARG("slow", INT, {
                auto slowTime = holder->getInt();
                if (slowTime > 1 && slowTime <= 64) {
                    tick::slowTick(slowTime);
                } else {
                    error(player, "number must in [2-64]");
                }
            }))
            ->then(ARG("wrap", INT, {
                auto wrapTime = holder->getInt();
                if (wrapTime > 1 && wrapTime <= 10) {
                    tick::wrapTick(wrapTime);
                } else {
                    error(player, "number must in [2-10]");
                }
            }))
            ->then(ARG("r", NONE, { tick::resetTick(); }))
            ->then(ARG("fw", INT, { tick::forwardTick(holder->getInt()); }));

    getCommandManager().registerCmd("./prof")->EXE({ tick::profileWorld(player); });

    getCommandManager().registerCmd("./mspt")->EXE({ tick::mspt(); });
    getCommandManager().registerCmd("./func")
            ->then(ARG("hc", BOOL, {
                enableHopperCounter = holder->getBool();
                info(player, "set hopper to %d", enableHopperCounter);
            }));

    getCommandManager().registerCmd("./counter")
            ->then(ARG("r", INT, { hopperCounterManager.resetChannel(player, holder->getInt()); }))
            ->then(ARG("p", INT, { hopperCounterManager.printChannel(player, holder->getInt()); }));

    getCommandManager().registerCmd("./gm")

            ->then(ARG("set", INT, {
                auto mode = holder->getInt();
                if (mode >= 0 && mode <= 3) {
                    player->setGameMode(holder->getInt());
                    info(player, "set gamemode to %d", mode);
                } else {
                    error(player, "mode must in [0-4]");
                }
            }));


    getCommandManager().registerCmd("./vill")
            ->then(ARG("list", NONE, { village::listVillages(player); }))
            ->then(ARG("show", BOOL, {
                enableVillageShow = holder->getBool();
                info(player, "set village show to %d", enableVillageShow);
            }));


    getCommandManager().registerCmd("./cfg")
            ->then(ARG("pvd", INT, {
                particleViewDistance = holder->getInt();
                info(player, "set particle view distance to %d", particleViewDistance);
            }));


    getCommandManager().registerCmd("./help")
            ->EXE({
                      info(player, "%s\n\n" \
                      "§r§6./tick fz - freeze the world\n"\
                    "./tick slow [num] -  slow the world\n"\
                    "./tick wrap [num] -  wrap the world\n" \
                    "./tick fw [num] - forward the world \n"\
                    "./vill draw [true/false] - (dis)enable the village bound and center show\n"\
                    "./vill list - list all the ticking villages\n"\
                    "./gm set [num] set gamemode num (3 is observer)\n" \
                    "./func hoppercounter/hc [true/false] - (dis)enable hopper counter\n"\
                    "./counter p [channel index] print counter data\n" \
                    "./counter r [channel index] reset channel data\n" \
                    "./prof - profile the level run health\n"\
                    "./conf pvd [distance] - config the particle view distance(default=128)\n-------------------\n",
                           version);
                  });

    getCommandManager().registerCmd("./dbg")
            ->EXE({
                      player->printInfo();
                  });

}

THook(void, //NOLINT
      MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334,
      void *self, std::string const &playerName,
      std::string &commandLine) {

    if (commandLine.rfind("./", 0) != 0) {
        return original(self, playerName, commandLine);
    }
    //获取发送命令的玩家
    Actor *cmdLauncherSource = nullptr;
    globalLevel->forEachPlayer([&playerName, &cmdLauncherSource](Actor *player) {
        if (player->getNameTag() == playerName) {
            cmdLauncherSource = player;
        }
    });
    //没找到直接返回
    if (!cmdLauncherSource)return original(self, playerName, commandLine);
    getCommandManager().parse(cmdLauncherSource, commandLine);
}



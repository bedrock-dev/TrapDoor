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
#include "Command.h"
#include "entity/Actor.h"
#include "block/Hopper.h"
#include "lib/version.h"
#include "level/Dimension.h"
#include "level/Level.h"

using namespace SymHook;


//注册命令
void initCommand() {
	getCommandManager()
		.registerCmd("tick", "改变时间流速")
		->then(ARG("fz", "冻结时间", NONE, { tick::freezeTick(); }))

		->then(ARG("slow", "将时间放慢到原来的 1/N", INT,
				   {
					   auto slowTime = holder->getInt();
					   if (slowTime > 1 && slowTime <= 64) {
						   tick::slowTick(slowTime);
					   } else {
						   error(player, "数值必须在 2-64 之中");
					   }
				   }))

		->then(ARG("acc", "将时间加快到原来的 N 倍", INT,
				   {
					   auto wrapTime = holder->getInt();
					   if (wrapTime > 1 && wrapTime <= 10) {
						   tick::wrapTick(wrapTime);
					   } else {
						   error(player, "数值必须在 2-10 之中");
					   }
				   }))

		->then(ARG("r", "重置时间流速", NONE, { tick::resetTick(); }))

		->then(ARG("fw", "时间前进 N 个游戏刻", INT,
				   { tick::forwardTick(holder->getInt()); }));

	getCommandManager().registerCmd("prof", "性能分析")->EXE({ tick::profileWorld(player); });

    getCommandManager().registerCmd("mspt", "显示 mspt 与 tps", MEMBER)->EXE({ tick::mspt(); });
	getCommandManager()
		.registerCmd("func", "启用/禁用功能")
		->then(ARG("hc", "启用/禁用漏斗计数器", BOOL,
				   {
					   enableHopperCounter = holder->getBool();
					   info(player, "%s漏斗计数器",
							enableHopperCounter ? "启用" : "禁用");
				   }))
		->then(ARG("exp", "启用/禁用爆炸", BOOL, {
			enableExplosion = holder->getBool();
			info(player, "%s爆炸", enableExplosion ? "启用" : "禁用");
		}));

	getCommandManager()
		.registerCmd("counter", "漏斗计数器频道", MEMBER)
		->then(ARG(
			"r", "重置频道 N", INT,
			{ hopperCounterManager.resetChannel(player, holder->getInt()); }))
		->then(ARG("p", "输出频道 N", INT, {
			hopperCounterManager.printChannel(player, holder->getInt());
		}));

	getCommandManager().registerCmd("o", "切换至旁观模式")
            ->EXE({
                      player->setGameMode(3);
                      info(player, "游戏模式已切换为旁观");
                  });

	getCommandManager().registerCmd("s", "切换至生存模式", MEMBER)->EXE({
		player->setGameMode(0);
		info(player, "游戏模式已切换为生存");
	});

	getCommandManager().registerCmd("c", "切换至创造模式")->EXE({
		player->setGameMode(1);
		info(player, "游戏模式已切换为创造");
	});

	getCommandManager().registerCmd("village", "村庄相关功能", MEMBER)
            ->then(ARG("list", "列出所有加载的村庄", NONE, { village::listVillages(player); }))
            ->then(ARG("show", "显示加载村庄的边界及其中心", BOOL, {
                enableVillageShow = holder->getBool();
                // info(player, "developing...");
            }));

    getCommandManager().registerCmd("cfg", "设置")
            ->then(ARG("pvd", "设置粒子显示半径", INT, {
                particleViewDistance = holder->getInt();
                info(player, "将粒子显示半径设置为 %d", particleViewDistance);
            }));


    getCommandManager().registerCmd("tr?", "帮助", MEMBER)
            ->EXE({
                      getCommandManager().printfHelpInfo(player);
                  });

    getCommandManager().registerCmd("dbg", "显示测试信息", MEMBER)
            ->EXE({
                      player->printInfo();
                  });

    getCommandManager().registerCmd("spawn", "显示刷怪信息")
            ->EXE({
                      player->getDimension()->printBaseTypeLimit();
                  });
}

// 调用下面的hook函数来吧自定义字符串和提示信息当作参数注入到游戏中
void regMCBECommand(const std::string &command, const char *description, CMD_LEVEL level) {
    if (!globalCommandRegistry) return;
    SYM_CALL(
            void(*)(void * cmdReg,const std::string&, const char*, char, char, char),
            MSSYM_MD5_8574de98358ff66b5a913417f44dd706,
            globalCommandRegistry,
            command, description, level, 0, level
    );
}


//? hook: 命令注册过程，服务器的命令注册和命令执行是分开的，二者并不绑定，因此可以直接调用这个函数来获得基本的命令提示
THook(
        void,
        MSSYM_MD5_8574de98358ff66b5a913417f44dd706,
        void *commandRegistry,
        const std::string &name,
        const char *str,
        char commandLevel,
        char flag1,
        char flag2
) {
    int newLevel = commandLevel > OP ? OP : commandLevel;
    //  printf("%-20s  %d %d %d\n", name.c_str(), commandLevel, flag1, flag2);
    original(commandRegistry, name, str, commandLevel, flag1, flag2);
    if (!globalCommandRegistry)globalCommandRegistry = commandRegistry;
}


// ? 这个函数用来处理BDS中的命令发送数据包
THook(
        void,
        MSSYM_B1QA6handleB1AE20ServerNetworkHandlerB2AAE26UEAAXAEBVNetworkIdentifierB2AAE24AEBVCommandRequestPacketB3AAAA1Z,
        void *handler,
        NetworkIdentifier *id,
        void * commandPacket
) {
    //根据玩家的网络id值来寻找发送命令的玩家
    Actor *source = nullptr;
    globalLevel->forEachPlayer([&id, &source](Actor *player) {
        if (player->getClientID()->getHash() == id->getHash()) {
            source = player;
            return;
        }
    });
    if (!source) {
        L_DEBUG("找不到有效玩家");
        original(handler, id, commandPacket);
        return;
    }

    //! 这是一处强制转换
    auto *commandString = reinterpret_cast<std::string *>((char *) commandPacket + 40);
    L_DEBUG("player %s execute command %s", source->getNameTag().c_str(), commandString->c_str());
    //截获命令数据包，获取命令字符串，如果是插件自定义的命令就直接处理，屏蔽原版，如果不是自定义命令就转发给原版去处理
    if (getCommandManager().findCommand(*commandString)) {
        //解析自定义命令
        getCommandManager().parse(source, *commandString);
    } else {
        //转发给原版
        original(handler, id, commandPacket);
    }

}

//std::string PlayerCommandOrigin::getName() {
//    return *SYM_CALL(
//            std::string*(*)(PlayerCommandOrigin * ),
//            MSSYM_B1QA7getNameB1AE29AutomationPlayerCommandOriginB2AAA4UEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
//            this
//    );
//}
//
//int PlayerCommandOrigin::getPermissionLevel() {
//    return SYM_CALL(
//            int(*)(PlayerCommandOrigin * ),
//            MSSYM_B1QE19getPermissionsLevelB1AE19PlayerCommandOriginB2AAA4UEBAB1QE25AW4CommandPermissionLevelB2AAA2XZ,
//            this
//    );;
//}


//THook(void, //NOLINT
//      MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334,
//      void *self, std::string const &playerName,
//      std::string &msg) {
//    dbg(msg);
//}
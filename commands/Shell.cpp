//
// Created by xhy on 2020/8/26.
//
#include <map>
#include <vector>
#include "lib/mod.h"
#include "lib/version.h"
#include "spawn/Spawn.h"
#include "village/Village.h"
//#include "src/tick/Tick.h"
#include "Shell.h"
#include "block/Hopper.h"
#include "entity/Actor.h"
#include "tick/GameTick.h"

/*
 * Dirty Command Parser
 * if else
 */

// typedef l );;
using namespace SymHook;
std::map<std::string, CmdType> commandMap = {  // NOLINT(cert-err58-cpp)
	{"./tick", CmdType::Tick},	  {"./prof", CmdType::Profile},
	{"./vill", CmdType::Village}, {"./func", CmdType::Function},
	{"./actor", CmdType::Spawn},  {"./help", CmdType::Help},
	{"./conf", CmdType::Config},  {"./counter", CmdType::Counter},
	{"./rand", CmdType::Rand},	  {"./mspt", CmdType::Mspt}};

void initCommand() {
	//    dbg("init commands");
	//    getCommandManager().registerCmd("./test")
	//            ->execute([](ArgHolder *holder) {
	//                printf("QAQ");
	////                globalLevel->forEachPlayer([](Actor *actor) {
	////                    printf("QAQ");
	////                });
	//            });
}

THook(void,	 // NOLINT
	  MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334,
	  void* self,
	  std::string const& playerName,
	  std::string& commandLine) {
	if (commandLine.rfind("./", 0) != 0) {
		return original(self, playerName, commandLine);
	}
	//获取发送命令的玩家
	Actor* cmdLauncherSource = nullptr;
	globalLevel->forEachPlayer(
		[&playerName, &cmdLauncherSource](Actor* player) {
			if (player->getNameTag() == playerName) {
				cmdLauncherSource = player;
			}
		});
	//没找到直接返回
	if (!cmdLauncherSource)
		return original(self, playerName, commandLine);

	//下面是要重写的代码
	auto tokens = tokenize(commandLine);
	auto result = commandMap.find(tokens[0]);
	if (result == commandMap.end()) {
		error(cmdLauncherSource, "unknown command , use [./help] to show help");
		return;
	}
	switch (result->second) {
		case CmdType::Tick:
			if (tokens.size() == 1)
				return;
			if (tokens[1] == "fz" || tokens[1] == "frozen") {  //重置为正常状态
				tick::freezeTick();
			} else if (tokens[1] == "reset" || tokens[1] == "r") {
				tick::resetTick();
			} else if (tokens[1] == "forward" ||
					   tokens[1] == "fw") {	 //前进n tick
				if (tokens.size() != 3)
					return;
				int time = strtol(tokens[2].c_str(), nullptr, 10);
				if (time <= 0) {
					error(cmdLauncherSource, "invalid parameter in time\n");
					return;
				}
				tick::forwardTick(time);

			} else if (tokens[1] == "slow") {
				if (tokens.size() != 3)
					return;
				int time = strtol(tokens[2].c_str(), nullptr, 10);
				if (time < 0) {
					error(cmdLauncherSource, "invalid parameter\n");
					return;
				}
				tick::slowTick(time);
			} else if (tokens[1] == "wrap") {  //加速 n 倍
				if (tokens.size() != 3)
					return;
				int time = strtol(tokens[2].c_str(), nullptr, 10);
				if (time < 1) {
					error(cmdLauncherSource,
						  "invalid parameter in time [1-10]\n");
					return;
				}
				tick::wrapTick(time);
			}
			break;
			// Profile
		case CmdType::Profile:
			tick::profileWorld(cmdLauncherSource);
			break;
		case CmdType::Mspt:
			// cmdLauncherSource->getBlockSource()->getBlock(4, 0,
			// 2)->getName();
			tick::mspt();
			break;
			// command about Village
		case CmdType::Village:
			info(cmdLauncherSource, "developing");
			return;
			if (tokens.size() == 1)
				return;
			if (tokens[1] == "draw") {
				if (tokens.size() == 3) {
					if (tokens[2] == "true") {
						enableVillageShow = true;
					} else if (tokens[2] == "false") {
						enableVillageShow = false;
					}
					return;
				} else {
					info(cmdLauncherSource, "use ./vill draw [true/false]");
				}
			} else if (tokens[1] == "list") {
				village::listVillages();
			}
			break;

		case CmdType::Function:
			if (tokens.size() != 3 ||
				!(tokens[2] == "true" || tokens[2] == "false")) {
				error(cmdLauncherSource,
					  "use ./func xxx [true/false]\nfor more info type /help");
				return;
			}
			if (tokens[1] == "extratickwork") {
				enableExtraTickWork = tokens[2] == "true";
			} else if (tokens[1] == "explosion") {
				enableExplosion = tokens[2] == "true";
			} else if (tokens[1] == "hoppercounter" || tokens[1] == "hc") {
				enableHopperCounter = tokens[2] == "true";
				info(cmdLauncherSource, "set hopper counter to %d",
					 tokens[2] == "true");
			} else if (tokens[1] == "positionmeasure" || tokens[1] == "pm") {
				info(cmdLauncherSource, "developing");
				//                enableMarkPos = tokens[2] == "true";
				//                info("set block measure to %d", tokens[2] ==
				//                "true");
			}
			break;
		case CmdType::Config:
			info(cmdLauncherSource, "developing");
			return;
			if (tokens.size() == 3) {
				if (tokens[1] == "particleViewDis" || tokens[1] == "pvd") {
					int distance = strtol(tokens[2].c_str(), nullptr, 10);
					if (distance > 0 && distance < 32768) {
						particleViewDistance = distance;
						info(cmdLauncherSource, "particle view set to %d",
							 distance);
					} else {
						error(cmdLauncherSource, "invalid distance");
					}
				} else if (tokens[1] == "rand") {
					uint64_t rand = stoll(tokens[2], nullptr, 16);
					info(cmdLauncherSource, "developing");
					// info(cmdLauncherSource, "set player rand to %llu", rand);
					// playerRand = rand;
				}
			} else {
				error(cmdLauncherSource, "unknown command");
			}
			break;
		case CmdType::Counter:
			if (tokens.size() != 3) {
				error(cmdLauncherSource, "use [./help] for help");
			} else {
				size_t channel = strtol(tokens[1].c_str(), nullptr, 10);
				if (tokens[2] == "p") {
					hopperCounterManager.printChannel(cmdLauncherSource,
													  channel);
				} else if (tokens[2] == "reset") {
					hopperCounterManager.resetChannel(cmdLauncherSource,
													  channel);
				} else {
					error(cmdLauncherSource, "unknown command");
				}
			}
			break;
		case CmdType::Help:
			info(cmdLauncherSource,
				 "§5§l          %s          \n"
				 "§r§6./tick fz - freeze the world\n"
				 "./tick slow [num] -  slow the world\n"
				 "./tick fw [num] - forward the world to num tick\n"
				 "./vill draw [true/false] - (dis)enable the village bound and "
				 "center show\n"
				 "./vill list - list all the ticking villages\n"
				 "./func explosion [true/false] - (dis)enable explosion\n"
				 "./func hoppercounter/hc [true/false] - (dis)enable hopper "
				 "counter\n"
				 "./func positionmeasure/pm [true/false] - (dis)enable block "
				 "measure\n"
				 "./counter [channel index] p print counter data\n"
				 "./counter [channel index] reset reset channel data\n"
				 "./prof - profile the level run health\n"
				 "./actor start -  start the mob spawner counter\n"
				 "./actor end -  end the mob spawner counter\n"
				 "./actor p -  print the counter result\n"
				 "./actor info -  print some mob info\n"
				 "./conf pvd [distance] - config the particle view "
				 "distance(default=128)\n-------------------\n",
				 version);
			// info("§rThanks:\n zhkj-liuxiaohua ΘΣΦΓΥΔΝ 莵道三室戸
			// 兰瑟头颅emm想无 TestBH 暮月云龙 其它相关SAC群友");
			break;

		case CmdType::Spawn:
			info(cmdLauncherSource, "developing");
			return;
			if (tokens.size() == 1)
				return;
			if (tokens[1] == "start") {
				startSpawnCounter();
			} else if (tokens[1] == "end") {
				endSpawnerCounter();
			} else if (tokens[1] == "p" || tokens[1] == "print") {
				auto str = tokens.size() == 3 ? tokens[2] : "null";
				spawnAnalysis(str);
			} else if (tokens[1] == "info") {
				sendMobInfo();
			}
		default:
			break;
	}
}

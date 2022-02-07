//
// Created by xhy on 2020/8/26.
//
#include "Command.h"

#include <map>
#include <random>
#include <vector>

#include "BDSMod.h"
#include "CommandNode.h"
#include "Message.h"
#include "MsgBuilder.h"
#include "Offset.h"
#include "entity/Actor.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    //注册命令
    // 调用下面的hook函数来吧自定义字符串和提示信息当作参数注入到游戏中
    // 注释这个函数一级指令就没提示了
    void regMCBECommand(const std::string &command, const char *description,
                        CommandPermissionLevel level, bool noCheat) {
        using namespace SymHook;
        if (!trapdoor::bdsMod) {
            L_ERROR("get a nullptr of trapdoor::mod");
            return;
        }
        if (!trapdoor::bdsMod->getCommandRegistry()) {
            L_ERROR("get a nullptr of trapdoor::mod::getCommandRegistry");
            return;
        }
        auto cheatOption = noCheat ? NoCheat : CommandFlag2::Cheat;
        SYM_CALL(void (*)(void *cmdReg, const std::string &, const char *, char,
                          char, char),
                 CommandRegistry_registerCommand_8574de98,
                 trapdoor::bdsMod->getCommandRegistry(), command, description,
                 level, None, cheatOption);
    }
}  // namespace trapdoor

//? hook:
//命令注册过程，服务器的命令注册和命令执行是分开的，二者并不绑定，因此可以直接调用这个函数来获得基本的命令提示
using namespace SymHook;

THook(void, CommandRegistry_registerCommand_8574de98, void *commandRegistry,
      const std::string &name, const char *str,
      trapdoor::CommandPermissionLevel level, trapdoor::CommandFlag1 flag1,
      trapdoor::CommandFlag2 flag2) {
    //这里是重新定义权限等级的，可以降低命令等级到游戏内执行
    auto newLevel = trapdoor::bdsMod->resetVanillaCommandLevel(name, level);
    original(commandRegistry, name, str, newLevel, flag1, flag2);
    //没有创建模组实例
    if (!trapdoor::bdsMod) {
        L_ERROR("get a nullptr of trapdoor::mod");
    } else {
        //初始化CommandRegistry 并且注册命令
        if (!trapdoor::bdsMod->getCommandRegistry()) {
            L_DEBUG("set command Registry %p", commandRegistry);
            trapdoor::bdsMod->setCommandRegistry(commandRegistry);
            L_DEBUG("init commandRegistry");
            trapdoor::bdsMod->registerCommands();
        }
    }
}

bool easterEggs(trapdoor::Actor *player, const std::string &cmd) {
    static std::unordered_map<std::string, size_t> ctr;
    if (cmd == "/hhhxiao") {
        auto playerName = player->getActorId();
        ctr[playerName]++;
        auto cnt = ctr[playerName];
        if (cnt == 1) {
            trapdoor::warning(player, "!");
        } else if (cnt == 3) {
            trapdoor::info(player,
                           "Player\n木月酸与云龙碱\n莵道三室戸\norange_31\n"
                           "panda4994万岁\n梵蒂冈_273\nOEOTYAN,\nOrigin 0110\n"
                           "阿阎mr\n玲珑芯\nSysca11\nyqs112358");
        } else if (cnt >= 5 && cnt <= 20) {
            using namespace trapdoor;
            static std::default_random_engine e(0);
            std::vector<uint8_t> cs;
            cs.push_back(MSG_COLOR::AQUA | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::YELLOW | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::GREEN | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::DARK_RED | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::BLUE | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::DARK_GREEN | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::LIGHT_PURPLE | MSG_COLOR::BOLD);
            cs.push_back(MSG_COLOR::RED | MSG_COLOR::BOLD);
            std::shuffle(cs.begin(), cs.end(), e);
            trapdoor::MessageBuilder b;
            int offset = e() % 5 + 5;
            for (int i = 0; i < offset; i++) {
                b.text(" ");
            }
            b.sText("T ", cs[0]);
            b.sText("R ", cs[1]);
            b.sText("A ", cs[2]);
            b.sText("P ", cs[3]);
            b.sText("D ", cs[4]);
            b.sText("O ", cs[5]);
            b.sText("O ", cs[6]);
            b.sText("R", cs[7]);
            b.send(player);
        }
        return true;
    } else {
        return false;
    }
}

//这个函数用来处理BDS中的命令发送数据包,也就是命令接口
THook(void, ServerNetworkHandler_handle_1a4c2996, void *handler,
      trapdoor::NetworkIdentifier *id, void *commandPacket) {
    //找到发送命令的玩家
    trapdoor::Actor *source = nullptr;
    trapdoor::bdsMod->getLevel()->forEachPlayer(
        [&id, &source](trapdoor::Actor *player) {
            if (player->getClientID()->getHash() == id->getHash()) {
                source = player;
                return;
            }
        });

    //找不到就直接返回
    if (!source) {
        L_DEBUG("can't not find valid player");
        original(handler, id, commandPacket);
        return;
    }

    L_DEBUG("find %s\n", source->getNameTag().c_str());
    //! 这是一处强制转换
    auto *commandString = reinterpret_cast<std::string *>(
        (char *)commandPacket + off::COMMAND_PACKET_STR);
    L_DEBUG("player %s execute command %s", source->getNameTag().c_str(),
            commandString->c_str());
    //截获命令数据包，获取命令字符串，如果是插件自定义的命令就直接处理，屏蔽原版，如果不是自定义命令就转发给原版去处理
    auto &commandManager = trapdoor::bdsMod->getCommandManager();
    if (commandManager.findCommand(*commandString)) {
        //解析命令
        commandManager.parse(source, *commandString);
    } else {
        if (!easterEggs(source, *commandString)) {
            original(handler, id, commandPacket);
        }
        //不是trapdoor的命令，转发给原版
    }
}
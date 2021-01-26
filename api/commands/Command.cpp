//
// Created by xhy on 2020/8/26.
//
#include "lib/mod.h"
#include "lib/SymHook.h"
#include <map>
#include <vector>
#include "Command.h"
#include "entity/Actor.h"
#include "BDSMod.h"
#include "tools/DirtyLogger.h"
#include "CommandNode.h"

namespace trapdoor {
//注册命令
// 调用下面的hook函数来吧自定义字符串和提示信息当作参数注入到游戏中
// 注释这个函数一级指令就没提示了
    void
    regMCBECommand(const std::string &command, const char *description, CommandPermissionLevel level, bool noCheat) {
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
        SYM_CALL(
                void(*)(void * cmdReg,
                const std::string&, const char*, char, char, char),
                MSSYM_MD5_8574de98358ff66b5a913417f44dd706,
                trapdoor::bdsMod->getCommandRegistry(),
                command, description, level, None, cheatOption
        );
    }
}


//? hook: 命令注册过程，服务器的命令注册和命令执行是分开的，二者并不绑定，因此可以直接调用这个函数来获得基本的命令提示
using namespace SymHook;

THook(
        void,
        MSSYM_MD5_8574de98358ff66b5a913417f44dd706,
        void *commandRegistry,
        const std::string &name,
        const char *str,
        trapdoor::CommandPermissionLevel level,
        trapdoor::CommandFlag1 flag1,
        trapdoor::CommandFlag2 flag2
) {
    //这里是重新定义权限等级的，可以降低命令等级到游戏内执行
    auto newLevel = trapdoor::bdsMod->resetVanillaCommandLevel(name, level);
    original(commandRegistry, name, str, newLevel, flag1, flag2);
    //没有创建模组实例
    if (!trapdoor::bdsMod) {
        L_ERROR("get a nullptr of trapdoor::mod");
    } else {
        //初始化CommandRegistry 并且注册命令
        if (!trapdoor::bdsMod->getCommandRegistry()) {
            trapdoor::bdsMod->setCommandRegistry(commandRegistry);
            L_INFO("init commandRegistry");
            trapdoor::bdsMod->registerCommands();
        }
    }
}

//这个函数用来处理BDS中的命令发送数据包,也就是命令接口
THook(
        void,
        MSSYM_B1QA6handleB1AE20ServerNetworkHandlerB2AAE26UEAAXAEBVNetworkIdentifierB2AAE24AEBVCommandRequestPacketB3AAAA1Z,
        void *handler,
        trapdoor::NetworkIdentifier *id,
        void * commandPacket
) {

    //找到发送命令的玩家
    trapdoor::Actor *source = nullptr;
    trapdoor::bdsMod->getLevel()->forEachPlayer([&id, &source](trapdoor::Actor *player) {
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

    //! 这是一处强制转换
    auto *commandString = reinterpret_cast<std::string *>((char *) commandPacket + 40);
    L_DEBUG("player %s execute command %s", source->getNameTag().c_str(), commandString->c_str());
    //截获命令数据包，获取命令字符串，如果是插件自定义的命令就直接处理，屏蔽原版，如果不是自定义命令就转发给原版去处理
    auto &commandManager = trapdoor::bdsMod->getCommandManager();
    if (commandManager.findCommand(*commandString)) {
        //解析命令
        commandManager.parse(source, *commandString);
    } else {
        //不是trapdoor的命令，转发给原版
        original(handler, id, commandPacket);
    }
}
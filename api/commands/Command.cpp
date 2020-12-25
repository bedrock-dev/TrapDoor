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

namespace trapdoor {
//注册命令
    using namespace SymHook;


// 调用下面的hook函数来吧自定义字符串和提示信息当作参数注入到游戏中
// 注释这个函数一级指令就没提示了
    void regMCBECommand(const std::string &command, const char *description, CMD_LEVEL level) {
        if (!trapdoor::bdsMod) {
            L_ERROR("get a nullptr of trapdoor::mod");
            return;
        }
        if (!trapdoor::bdsMod->getCommandRegistry()) {
            L_ERROR("get a nullptr of trapdoor::mod::getCommandRegistry");
            return;
        }
        SYM_CALL(
                void(*)(void * cmdReg,
                const std::string&, const char*, char, char, char),
                MSSYM_MD5_8574de98358ff66b5a913417f44dd706,
                trapdoor::bdsMod->getCommandRegistry(),
                command, description, level, 0, level
        );
    }

    //todo
//? hook: 命令注册过程，服务器的命令注册和命令执行是分开的，二者并不绑定，因此可以直接调用这个函数来获得基本的命令提示
    namespace SymHook {
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
                NetworkIdentifier *id,
                void * commandPacket
        ) {

            Actor *source = nullptr;
            trapdoor::bdsMod->getLevel()->forEachPlayer([&id, &source](Actor *player) {
                if (player->getClientID()->getHash() == id->getHash()) {
                    source = player;
                    return;
                }
            });

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
                //转发给原版
                original(handler, id, commandPacket);
            }
        }

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
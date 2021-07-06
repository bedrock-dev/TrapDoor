

#include "FunctionCommands.h"
#include "commands/CommandNode.h"
#include "commands/ArgHolder.h"
#include "language/I18nManager.h"
#include "tools/Message.h"
namespace mod{
//便捷模式切换
    void registerGamemodeSwitchCommand(CommandManager & commandManager){
        using namespace trapdoor;
        commandManager.registerCmd("o", "command.o.desc")
                ->EXE({
                          player->setGameMode(4);
                          broadcastMsg(LANG("command.o.set"),
                                       player->getNameTag().c_str());
                      });

        commandManager.registerCmd("s", "command.s.desc")
                ->EXE({
                          player->setGameMode(0);
                          broadcastMsg(LANG("command.s.set"), player->getNameTag().c_str());
                      });

        commandManager.registerCmd("c", "command.c.desc")
                ->EXE({
                          player->setGameMode(1);
                          broadcastMsg(LANG("command.c.set"), player->getNameTag().c_str());
                      });
    } 
} // namespace mod



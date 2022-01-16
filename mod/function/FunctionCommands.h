#ifndef MOD_FUNCTION_COMMANDS
#define MOD_FUNCTION_COMMANDS

#include "commands/CommandManager.h"
#include "entity/Actor.h"


namespace mod {
    void registerGamemodeSwitchCommand(CommandManager& commandManager);

    void printfSysInfo(trapdoor::Actor* player);

}  // namespace mod

#endif

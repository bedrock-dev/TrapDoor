//
// Created by xhy on 2021/1/9.
//

#ifndef MOD_BACKUPHELPER_H
#define MOD_BACKUPHELPER_H

#include "commands/CommandManager.h"
#include "entity/Actor.h"

namespace mod {
void backup(trapdoor::Actor *player);

void listAllBackups(trapdoor::Actor *player);

void initBackup();

void restore(trapdoor::Actor *player, int index = 0);

void registerBackupCommand(trapdoor::CommandManager &commandManager);
} // namespace mod

#endif // MOD_BACKUPHELPER_H

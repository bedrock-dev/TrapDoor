//
// Created by xhy on 2021/1/9.
//

#ifndef MOD_BACKUPHELPER_H
#define MOD_BACKUPHELPER_H

#include "commands/CommandManager.h"
#include "entity/Actor.h"

namespace mod {
    void initBackup();

    void registerBackupCommand(trapdoor::CommandManager &commandManager);

}  // namespace mod

#endif  // MOD_BACKUPHELPER_H

//
// Created by xhy on 2021/1/9.
//

#ifndef MOD_BACKUPHELPER_H
#define MOD_BACKUPHELPER_H

#include "entity/Actor.h"
#include "filesystem"

namespace mod {
    void backup(trapdoor::Actor *player);

    void listAllBackups(trapdoor::Actor *player);


    void initBackup();
}

#endif //MOD_BACKUPHELPER_H

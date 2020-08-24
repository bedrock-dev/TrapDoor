//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_VILLAGERHOOK_H
#define TRAPDOOR_VILLAGERHOOK_H

#include "Village.h"

namespace SymHook {
    //village tick
    THook(
            void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
            void *vill, void *tick, void * blockSource
    ) {
        original(vill, tick, blockSource);
        villageHelper.insert(vill);
    }

}

#endif //TRAPDOOR_VILLAGERHOOK_H

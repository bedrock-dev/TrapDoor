//
// Created by xhy on 2020/12/23.
//
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"

namespace mod {
    using namespace SymHook;

    THook(
            void,
            MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ,
            void * exp
    ) {
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        if (!modInstance->getSingFunction().preventExplosion)
            original(exp);
    }

    /**
     *  SYM_CALL(
                void(*)(BlockSource * self,const BlockPos *pos),
                MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
                this, pos
        );
     */

    THook(
            void,
            MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
            trapdoor::BlockSource *source,
            trapdoor::BlockPos * pos
    ) {
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        if (!modInstance->getSingFunction().preventNCUpdate)
            original(source, pos);
    }
}
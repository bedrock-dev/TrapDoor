//
// Created by xhy on 2020/12/23.
//

#include "BDSMod.h"
#include "TrapdoorMod.h"

namespace mod {


    /**
     *  SYM_CALL(
                void(*)(BlockSource * self,const BlockPos *pos),
                MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
                this, pos
        );
     */
}

THook(void, "?explode@Explosion@@QEAAXXZ", void* exp) {
    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
    if (!modInstance->getSingFunction().preventExplosion)
        original(exp);
}

THook(
    void,
    "?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z",
    trapdoor::BlockSource* source,
    trapdoor::BlockPos* pos
) {
    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
    if (!modInstance->getSingFunction().preventNCUpdate)
        original(source, pos);
}
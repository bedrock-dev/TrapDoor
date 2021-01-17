//
// Created by xhy on 2021/1/14.
//

#include "POIInstance.h"
#include "lib/mod.h"
#include "lib/SymHook.h"

namespace mod {
    DwellerComponent *mod::getDwellerComponentFromActor(trapdoor::Actor *actor) {
        return SYM_CALL(
                mod::DwellerComponent*(*)(trapdoor::Actor * ),
                SymHook::MSSYM_B3QQDE15tryGetComponentB1AE17VDwellerComponentB3AAAA5ActorB2AAE24QEAAPEAVDwellerComponentB2AAA2XZ,
                actor
        );
    }

    trapdoor::BlockPos *DwellerComponent::getVillageCenter(trapdoor::Actor *actor) {
        trapdoor::BlockPos pos;
        return SYM_CALL(
                trapdoor::BlockPos*(*)(DwellerComponent * , trapdoor::BlockPos *, trapdoor::Actor * actor),
                SymHook::MSSYM_B1QE16getVillageCenterB1AE16DwellerComponentB2AAA4QEBAB1QE10AVBlockPosB2AAA9AEBVActorB3AAAA1Z,
                this,
                &pos,
                actor
        );
    }
};


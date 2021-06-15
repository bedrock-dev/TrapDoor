//
// Created by xhy on 2021/1/14.
//

#include "POIInstance.h"
#include "Loader.h"
namespace mod {
    DwellerComponent *mod::getDwellerComponentFromActor(trapdoor::Actor *actor) {
        return SymCall("??$tryGetComponent@VDwellerComponent@@@Actor@@QEAAPEAVDwellerComponent@@XZ"
            , mod::DwellerComponent*, trapdoor::Actor*)(actor
        );
    }

    trapdoor::BlockPos *DwellerComponent::getVillageCenter(trapdoor::Actor *actor) {
        trapdoor::BlockPos pos;
        return SymCall("?getVillageCenter@DwellerComponent@@QEBA?AVBlockPos@@AEBVActor@@@Z"
            ,trapdoor::BlockPos*, DwellerComponent*, trapdoor::BlockPos*, trapdoor::Actor *)(this,&pos,actor);
    }
};


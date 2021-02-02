//
// Created by xhy on 2021/2/1.
//

#include "lib/mod.h"
#include "lib/SymHook.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"

namespace mod {
    using namespace SymHook;
    namespace {
        bool enableBetterMSPT() {
            return trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()->getSingFunction().enableBetterMspt;
        }
    }
    THook(
            void,
            MSSYM_B2QUE25checkInceptionAchievementB1AE16PistonBlockActorB2AAE19AEAAXAEAVBlockActorB2AAE15AEAVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z,
            void *pistonBlockActor,
            void *be, void *region, void * facingDir
    ) {
        if (!enableBetterMSPT()) original(pistonBlockActor, be, region, facingDir);
    }
}
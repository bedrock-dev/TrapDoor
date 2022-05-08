//
// Created by xhy on 2020/12/23.
//

#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "lib/SymHook.h"
#include "lib/mod.h"

namespace mod {
    using namespace SymHook;

    THook(void, Explosion_explode_5adcea90, void *exp) {
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        if (!modInstance->getSingFunction().preventExplosion) original(exp);
    }

    /**
     *  SYM_CALL(
                void(*)(BlockSource * self,const BlockPos *pos),
                MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
                this, pos
        );
     */

    THook(void, BlockSource_updateNeighborsAt_4c3f8cf7,
          trapdoor::BlockSource *source, trapdoor::BlockPos *pos) {
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        if (!modInstance->getSingFunction().preventNCUpdate)
            original(source, pos);
    }
    // 0X15EDAD0
    constexpr uint64_t Continaer_can_open = 0X15EDAD0;
    THook(bool, Continaer_can_open, void *container, void *bs) {
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        if (!modInstance->getSingFunction().noConatinerObstruct) {
            return true;
        } else {
            return original(container, bs);
        }
    }

    /*
0XEA71D0
public: virtual void __cdecl Container::removeItem(int,int) __ptr64
?removeItem@Container@@UEAAXHH@Z
    */
    constexpr uint64_t Continaer_remove_item = 0XEA71D0;
    THook(void, Continaer_remove_item, void *container, int slot, int count) {
        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        if (!modInstance->getSingFunction().noContainerCost) {
            original(container, slot, count);
        }
    }
}  // namespace mod
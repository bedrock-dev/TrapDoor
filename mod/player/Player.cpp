//
// Created by xhy on 2020/8/29.
//



#include <cstdint>
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "block/Block.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "PlayerStatisticManager.h"
#include "Player.h"

//player place block
using namespace SymHook;
//
//THook(
//        int64_t,
//        MSSYM_B1QE21onBlockPlacedByPlayerB1AE34VanillaServerGameplayEventListenerB2AAA4UEAAB1QE14AW4EventResultB2AAE10AEAVPlayerB2AAA9AEBVBlockB2AAE12AEBVBlockPosB3AAUA1NB1AA1Z,
//        void *self,
//        trapdoor::Actor *player,
//        trapdoor::Block &block,
//        const trapdoor::BlockPos &pos,
//        bool flag
//) {
//    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
//    modInstance->getPlayerStatisticManager().insetPlayerAction(player->getNameTag(), pos,
//                                                               mod::PlayerStatisticManager::PLACE_BLOCK,
//                                                               player->getDimensionID(),
//                                                               block.getName());
//
//    return original(self, player, block, pos, flag);
//}
//player destroy block
//
//THook(
//        void,
//        MSSYM_B2QUE20destroyBlockInternalB1AA8GameModeB2AAA4AEAAB1UE13NAEBVBlockPosB2AAA1EB1AA1Z,
//        uint64_t *self,
//        const trapdoor::BlockPos *pos,
//        int64_t a3,
//        int a4
//) {
//    uint64_t *ptr = self + 1;
//    auto player = reinterpret_cast<trapdoor::Actor *>(*ptr);
//    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
//    auto block = player->getBlockSource()->getBlock(pos->x, pos->y, pos->z);
//    modInstance->getPlayerStatisticManager().insetPlayerAction(player->getNameTag(), *pos,
//                                                               mod::PlayerStatisticManager::DESTROY_BLOCK,
//                                                               player->getDimensionID(),
//                                                               block->getName());
//    original(self, pos, a3, a4);
//}



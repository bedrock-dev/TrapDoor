//
// Created by xhy on 2020/8/29.
//

#include "HopperCounter.h"

#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "block/BlockSource.h"
#include "entity/Item.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"

using namespace SymHook;

namespace mod {

    const size_t HopperChannelManager::TOTAL_CHANNEL_NUM = 16;
    const trapdoor::BlockType HopperChannelManager::BLOCK_TYPE =
        trapdoor::CONCRETE;

    void HopperChannelManager::tick() {
        if (this->enable) {
            for (auto &channel : channels) {
                channel.tick();
            }
        }
    }

    void HopperChannelManager::printChannel(Actor *player, size_t channel) {
        if (channel < 0 || channel > 15) {
            error(player, "该频道不存在[0-15]");
        } else {
            getChannel(channel).print(player);
        }
    }

    void HopperChannelManager::resetChannel(Actor *player, size_t channel) {
        if (channel < 0 || channel > 15) {
            error(player, "该频道不存在");
        } else {
            getChannel(channel).reset();
            trapdoor::broadcastMsg("频道[%zu] 数据已重置", channel);
        }
    }

    void HopperChannelManager::registerCommand(CommandManager &commandManager) {
        commandManager.registerCmd("counter", "command.counter.desc")
            ->then(Arg("r", "command.counter.r.desc", ArgType::INT)
                       ->execute([this](ArgHolder *holder, Actor *player) {
                           this->resetChannel(player, holder->getInt());
                       }))
            ->then(Arg("p", "command.counter.p.desc", ArgType::INT)
                       ->execute([this](ArgHolder *holder, Actor *player) {
                           this->printChannel(player, holder->getInt());
                       }));
    }

    void HopperChannelManager::quickPrintData(trapdoor::Actor *player,
                                              trapdoor::BlockPos &pos) {
        if (!this->enable) return;
        auto *block = player->getBlockSource()->getBlock(pos);
        if (block->getLegacy()->getBlockID() !=
            HopperChannelManager::BLOCK_TYPE)
            return;
        this->printChannel(player, block->getVariant());
    }

    void CounterChannel::add(const std::string &itemName, size_t num) {
        counterList[itemName] += num;
    }

    void CounterChannel::reset() {
        gameTick = 0;
        counterList.clear();
    }

    void CounterChannel::print(Actor *actor) {
        int n = 0;
        for (const auto &i : this->counterList) {
            n += i.second;
        }

        if (this->gameTick == 0 || n == 0) {
            L_DEBUG("tick = %d num = %d", gameTick, n);
            info(actor, "no data in this channel");
            return;
        }
        std::string stringBuilder;
        trapdoor::MessageBuilder builder;
        stringBuilder +=
            trapdoor::format("channel: " C_INT "\ntotal " C_INT
                             " items in " C_INT " gt(" C_FLOAT "min)\n",
                             channel, n, gameTick, gameTick / 1200.0);
        for (const auto &i : counterList) {
            stringBuilder += trapdoor::format(
                "- %s  " C_INT "(" C_FLOAT "/hour)\n", i.first.c_str(),
                i.second, i.second * 1.0 / gameTick * 72000);
        }
        trapdoor::info(actor, stringBuilder);
    }
}  // namespace mod

THook(void, HopperBlockActor_setItem_c0e5f3ce,
      trapdoor::BlockActor *hopperActor, unsigned int index,
      trapdoor::ItemStackBase *itemStack) {
    //计数器没开启，直接返回
    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
    if (!modInstance->getHopperChannelManager().isEnable()) {
        original(hopperActor, index, itemStack);
        return;
    }

    //附近没玩家，直接返回
    auto real_this = reinterpret_cast<trapdoor::BlockActor *>(
        reinterpret_cast<VA>(hopperActor) - 200);
    auto position = real_this->getPosition();
    L_DEBUG("postion is:%d %d %d", position->x, position->y, position->z);
    auto nearestPlayer =
        trapdoor::bdsMod->getLevel()->getNearestPlayer(*position);
    if (!nearestPlayer) {
        original(hopperActor, index, itemStack);
        return;
    }
    auto bs = nearestPlayer->getBlockSource();
    auto hopperBlockVariant =
        (trapdoor::FACING)bs->getBlock(*position)->getVariant();
    auto attachBlockPos =
        trapdoor::facingToBlockPos(hopperBlockVariant) + *position;
    auto attachBlock = bs->getBlock(attachBlockPos);
    L_DEBUG("name: %s, variant: %d", attachBlock->getName().c_str(),
            attachBlock->getVariant());
    int stackNum = itemStack->getNum();
    std::string itemName = itemStack->getItemName();
    auto channel = attachBlock->getVariant();
    auto blockId = attachBlock->getLegacy()->getBlockID();
    if (blockId == mod::HopperChannelManager::BLOCK_TYPE) {
        if (!itemName.empty()) {
            modInstance->getHopperChannelManager().getChannel(channel).add(
                itemName, stackNum);
        } else {
            original(hopperActor, index, itemStack);
        }
    } else {
        original(hopperActor, index, itemStack);
    }
}
//下面是一些漏斗性能的测试代码，不用管
// 0x00CCE6D0
// ?_tryMoveItems@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@AEBVVec3@@H_N@Z
//(class BlockSource & __ptr64,class Container & __ptr64,class Vec3 const &
//__ptr64,int,bool) __ptr64
// constexpr SymHook::RVA SYM_hopper_trymove_item = 0x00CCE6D0;
// THook(void, SYM_hopper_trymove_item, void *block, void *region,
//       void *fromContainer, void *pos, int attachedFace, bool canPushItems) {
//     rmt_ScopedCPUSample(HOPPER_MOVE_ITEM, 0);
//     original(block, region, fromContainer, pos, attachedFace, canPushItems);
// }

// // 0x010DB8D0
// ?_ensureTickingOrder@HopperBlockActor@@AEAAXAEAVBlockSource@@H@Z

// constexpr SymHook::RVA SYM_ensureTickOrder = 0x010DB8D0;
// THook(void, SYM_ensureTickOrder, void *block, void *bs, int rec) {
//     rmt_ScopedCPUSample(ENSURE_ORDER, 0);
//     original(block, bs, rec);
// }

// //# [ԭ��] protected: bool __cdecl Hopper::_tryTakeInItemFromSlot(class
// // BlockSource & __ptr64,class Container & __ptr64,class Container &
// //__ptr64,int,int) __ptr64 0x00CCF410
// //
// ?_tryTakeInItemFromSlot@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@1HH@Z

// constexpr SymHook::RVA SYM_tryTakcItem = 0x00CCF410;

// THook(bool, SYM_tryTakcItem, void *self, void *region, void *toContainer,
//       void *fromContainer, int slot, int face) {
//     rmt_ScopedCPUSample(TAKE_A_ITEM, 0);
//     return original(self, region, toContainer, fromContainer, slot, face);
// }

// //# [ԭ��] protected: bool __cdecl Hopper::_isEmptyContainer(class
// Container
// //&
// //__ptr64,int) __ptr64 0x00CCAEF0
// // ?_isEmptyContainer@Hopper@@IEAA_NAEAVContainer@@H@Z

// constexpr SymHook::RVA SYM_HopperIsEmpty = 0x00CCAEF0;

// THook(bool, SYM_HopperIsEmpty, void *hopper, void *c, int a) {
//     rmt_ScopedCPUSample(HOPPER_EMPTY_CHECK, 0);
//     return original(hopper, c, a);
// }

// constexpr SymHook::RVA SYM_Item_Isnull = 0x00C88A10;
// constexpr SymHook::RVA SYm_Item_getMaxStackSize = 0x00C863D0;

// bool isNull(trapdoor::ItemStackBase *item) {
//     return SYM_CALL(bool (*)(trapdoor::ItemStackBase *), SYM_Item_Isnull,
//     item);
// }

// unsigned char getMaxStackSize(trapdoor::ItemStackBase *item) {
//     return SYM_CALL(unsigned char (*)(trapdoor::ItemStackBase *),
//                     SYm_Item_getMaxStackSize, item);
// }

// //# [ԭ��] protected: bool __cdecl Hopper::_isFullContainer(class
// // BlockSource
// //&
// //__ptr64,class Container & __ptr64,int) __ptr64 0x00CCAF80
// // ?_isFullContainer@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@H@Z

// constexpr SymHook::RVA SYM_ContainerGetSlots = 0x00BDAAE0;

// void getSlotsFromContainer(void *container,
//                            std::vector<trapdoor::ItemStackBase *> *slots)

// {
//     SYM_CALL(void (*)(void *, std::vector<trapdoor::ItemStackBase *> *),
//              SYM_ContainerGetSlots, container, slots);
// }

// constexpr SymHook::RVA SYM_HopperIsFull = 0x00CCAF80;
// THook(bool, SYM_HopperIsFull, void *hopper, void *bs, void *c, int a) {
//     // rmt_ScopedCPUSample(HOPPER_FULL_CHECK, 0);

//     std::vector<trapdoor::ItemStackBase *> slots;
//     getSlotsFromContainer(c, &slots);
//     for (const auto &i : slots) {
//         if (isNull(i)) {
//             return false;
//         }
//         if (i->getNum() < getMaxStackSize(i)) {
//             return false;
//         }
//     }
//     return true;
//     //    return original(hopper, bs, c, a);
//     // return false;
// }

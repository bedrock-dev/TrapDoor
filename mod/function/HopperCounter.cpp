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
            error(player, "该频道不存在，范围在[0-15]内");
        } else {
            getChannel(channel).print(player);
        }
    }

    void HopperChannelManager::resetChannel(Actor *player, size_t channel) {
        if (channel < 0 || channel > 15) {
            error(player, "该频道不存在");
        } else {
            getChannel(channel).reset();
            trapdoor::broadcastMsg("频道[%zu]的数据已重置", channel);
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
        builder.textF("Channel [%d]: Total %d items in %d gt (%.3f min(s))\n",
                      channel, n, gameTick, gameTick / 1200.0);

        for (const auto &i : counterList) {
            auto itemName = GetItemLocalName(i.first);
            builder.textF(" - %s: ", itemName.c_str())
                .sTextF(trapdoor::MSG_COLOR::GREEN, "%d", i.second)
                .text("(")
                .sTextF(trapdoor::MSG_COLOR::GREEN, "%.3f",
                        i.second * 1.0 / gameTick * 72000)
                .text("/hour)\n");
        }
        builder.send(actor);
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
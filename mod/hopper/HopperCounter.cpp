//
// Created by xhy on 2020/8/29.
//

#include "entity/Item.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "HopperCounter.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "BDSMod.h"
#include "tools/DirtyLogger.h"
#include "block/BlockSource.h"
#include "tools/MsgBuilder.h"
#include "TrapdoorMod.h"

using namespace SymHook;


namespace mod {
    const std::map<std::string, size_t> HopperChannelManager::BLOCK_NAME_CHANNEL_MAPPER = {//NOLINT
            {"minecraft:diamond_block", 0}, //钻石
            {"minecraft:emerald_block", 1}, //绿宝石
            {"minecraft:iron_block",    2},  //铁
            {"minecraft:gold_block",    3}, //金子
            {"minecraft:lapis_block",   4} //青金石
    };

    void HopperChannelManager::tick() {
        if (this->enable) {
            for (auto &channel :channels) {
                channel.tick();
            }
        }
    }
    void HopperChannelManager::printChannel(Actor *player, size_t channel) {
        if (channel < 0 || channel > 4) {
            error(player, "this channel do not exist");
        } else {
            getChannel(channel).print(player);
        }
    }

    void HopperChannelManager::resetChannel(Actor *player, size_t channel) {
        if (channel < 0 || channel > 4) {
            error(player, "this channel do not exist");
        } else {
            getChannel(channel).reset();
            trapdoor::broadcastMsg("channel[%zu] reset", channel);
        }
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
        for (const auto &i:this->counterList) {
            n += i.second;
        }

        if (this->gameTick == 0 || n == 0) {
            L_DEBUG("tick = %d num = %d", gameTick, n);
            info(actor, "no data in this channel");
            return;
        }
        trapdoor::MessageBuilder builder;
        builder.sTextF(trapdoor::MessageBuilder::BOLD, "channel %d\n", channel)
                .num(n).text("  items in ").num(gameTick).text(" gt(").num(gameTick / 1200.0).text("min)\n");
        for (const auto &i:counterList) {
            builder.textF(" - ").text(i.first).text("    ").num(i.second).text("(").num(i.second * 1.0 / gameTick * 72000).text(
                    "min)\n");
        }
        builder.send(actor);
    }
}

THook(
        void,
        MSSYM_B1QA7setItemB1AE16HopperBlockActorB2AAE19UEAAXHAEBVItemStackB3AAAA1Z,
        void *hopperActor,
        unsigned int index,
        trapdoor::ItemStackBase * itemStack
) {


    auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
    if (!modInstance->getHopperChannelManager().isEnable()) {
        original(hopperActor, index, itemStack);
        return;
    }


    auto real_this = reinterpret_cast<void *>(reinterpret_cast<VA>(hopperActor) - 208);
    auto blockPos = reinterpret_cast<trapdoor::BlockActor *>(real_this)->getPosition();
    std::string itemName = itemStack->getItemName();

    int stackNum = itemStack->getNum();
    trapdoor::BlockPos pos(blockPos->x, blockPos->y, blockPos->z);
    auto nearestPlayer = trapdoor::bdsMod->getLevel()->getNearestPlayer(pos);
    if (!nearestPlayer) {
        original(hopperActor, index, itemStack);
        //  L_DEBUG("can't find a valid player");
        return;
    }

    auto blockSource = nearestPlayer->getBlockSource();
    auto block = blockSource->getBlock(blockPos->x, blockPos->y - 1, blockPos->z);
    std::string blockName = block->getName();
    auto result = mod::HopperChannelManager::BLOCK_NAME_CHANNEL_MAPPER.find(blockName);
    if (result != mod::HopperChannelManager::BLOCK_NAME_CHANNEL_MAPPER.end()) {
        if (!itemName.empty()) {
            modInstance->getHopperChannelManager().getChannel(result->second).add(itemName, stackNum);
        } else {
            original(hopperActor, index, itemStack);
        }
    } else {
        original(hopperActor, index, itemStack);
    }
}


//
// Created by xhy on 2020/8/29.
//

#include "Hopper.h"
#include "entity/Item.h"
#include "block/Block.h"
#include "common/Common.h"
#include "tools/Message.h"
#include "tools/MessageBuilder.h"

using namespace SymHook;
const std::map<std::string, size_t> ChannelManager::BLOCK_NAME_CHANNEL_MAPPER = {//NOLINT
        {"minecraft:diamond_block", 0},
        {"minecraft:emerald_block", 1},
        {"minecraft:iron_block",    2},
        {"minecraft:gold_block",    3},
        {"minecraft:lapis_block",   4}
};

void ChannelManager::printAll() {
    for (auto channel:this->channels) {
        channel.print();
    }
}

void ChannelManager::tick() {
    if (!enableHopperCounter)return;
    for (auto &i:channels) {
        i.t();
    }
}

void ChannelManager::printChannel(size_t channel) {
    if (channel < 0 || channel > 4) {
        error("this channel do not exist");
    } else {
        getChannel(channel).print();
    }
}

void ChannelManager::resetChannel(size_t channel) {
    if (channel < 0 || channel > 4) {
        error("this channel do not exist");
    } else {
        getChannel(channel).reset();
        info("channel reset");
    }
}

ChannelManager hopperCounterManager; //NOLINT

THook(
        void,
        MSSYM_B1QA7setItemB1AE16HopperBlockActorB2AAE19UEAAXHAEBVItemStackB3AAAA1Z,
        void *hopperActor,
        unsigned int index,
        ItemStackBase * itemStack
) {
    auto real_this = reinterpret_cast<void *>(reinterpret_cast<VA>(hopperActor) - 208);
    auto blockPos = reinterpret_cast<BlockActor *>(real_this)->getPosition();
    if (enableHopperCounter) {
        std::string itemName = itemStack->getItemName();
        int stackNum = itemStack->getNum();

        auto block = globalBlockSource->getBlock(blockPos->x, blockPos->y - 1, blockPos->z);
        std::string blockName = block->getName();

        //find channel
        auto result = ChannelManager::BLOCK_NAME_CHANNEL_MAPPER.find(blockName);
        if (result != ChannelManager::BLOCK_NAME_CHANNEL_MAPPER.end()) {
            if (globalPlayer && !itemName.empty()) {
                hopperCounterManager.getChannel(result->second).add(itemName, stackNum);
            }
        }

    } else {
        original(hopperActor, index, itemStack);
    }
}

void CounterChannel::add(const std::string &itemName, size_t num) {
    counterList[itemName] += num;
}

void CounterChannel::reset() {
    tick = 0;
    counterList.clear();
}

void CounterChannel::print() {

    int num = 0;
    for (const auto &i:this->counterList) {
        num += i.second;
    }
    if (this->tick == 0 || num == 0) {
        info("no data in this channel");
        return;
    }
    std::vector<uint8_t> color = {
            COLOR::AQUA,
            COLOR::GREEN,
            COLOR::WHITE,
            COLOR::GOLD,
            COLOR::BLUE
    };
    MessageBuilder builder;
    builder.sText("channel ", COLOR::BOLD | color[this->channel])
            .sText(std::to_string(this->channel), COLOR::BOLD | color[this->channel])
            .text("\n")
            .num(tick).text("  gt (")
            .num((float) tick / 1200.0)
            .text(" min)\n----------\n");
    for (const auto &i:counterList) {
        builder.text(i.first)
                .text(":        ")
                .num(i.second)
                .text("  (")
                .num((float) i.second * 72000 / (float) tick)
                .text("/h)\n");
        // gamePrintf("%s: %zu(%.2f/h)\n", i.first.c_str(), i.second, (float) i.second * 72000 / (float) tick);
    }
    builder.send();
}

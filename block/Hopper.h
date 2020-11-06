//
// Created by xhy on 2020/8/29.
//

#ifndef TRAPDOOR_HOPPER_H
#define TRAPDOOR_HOPPER_H
//: minecraft:hopper" (std::string)
//[..or\entity\Player.cpp:29 (_hook)] name = "name: minecraft:diamond_block" (std::string)
//[..or\entity\Player.cpp:29 (_hook)] name = "name: minecraft:emerald_block" (std::string)
//[..or\entity\Player.cpp:29 (_hook)] name = "name: minecraft:iron_block" (std::string)
//[..or\entity\Player.cpp:29 (_hook)] name = "name: minecraft:gold_block" (std::string)
//[..or\entity\Player.cpp:29 (_hook)] name = "name: minecraft:lapis_block"



#include "lib/pch.h"
#include "lib/mod.h"
#include <map>
#include <array>
#include <vector>

class Actor;


class CounterChannel {
    const size_t channel;
    std::map<std::string, size_t> counterList;
    unsigned long long tick;
public:
    explicit CounterChannel(size_t ch) : channel(ch), tick(0) {}

    void reset();

    void print(Actor *actor);

    void add(const std::string &itemName, size_t num);

    inline void t() {
        ++tick;
    }
};


class ChannelManager {
    std::vector<CounterChannel> channels;
public:
    static const std::map<std::string, size_t> BLOCK_NAME_CHANNEL_MAPPER;

    ChannelManager() {
        for (int i = 0; i < 5; i++)
            channels.emplace_back(i);
    }

    inline CounterChannel &getChannel(const int &ch) {
        return channels[ch];
    }

    void tick();

    void printAll();

    void printChannel(Actor *player , size_t channel);

    void resetChannel(Actor *player,size_t channel);
};

extern ChannelManager hopperCounterManager;

#endif //TRAPDOOR_HOPPER_H

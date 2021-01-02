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


#include "lib/mod.h"
#include <map>
#include <array>
#include <vector>
#include "entity/Actor.h"
#include "block/Block.h"

//漏斗计数器频道
namespace mod {

    using Actor = trapdoor::Actor;
    using BlockActor = trapdoor::BlockActor;
    using BlockPos = trapdoor::BlockPos;

    class CounterChannel {
        const size_t channel;
        std::map<std::string, size_t> counterList;
        Tick gameTick = 0;
    public:
        explicit CounterChannel(size_t ch) : channel(ch), gameTick(0) {}

        void reset();

        void print(Actor *actor);

        void add(const std::string &itemName, size_t num);

        inline void tick() {
            ++gameTick;
        }
    };

//漏斗频道管理器
    class HopperChannelManager {
        std::vector<CounterChannel> channels;
        bool enable = false;
    public:
        static const std::map<std::string, size_t> BLOCK_NAME_CHANNEL_MAPPER;

        HopperChannelManager() {
            for (int i = 0; i < 5; i++)
                channels.emplace_back(i);
        }

        inline CounterChannel &getChannel(const int &ch) {
            return channels[ch];
        }

        //更新计数器
        void tick();

        inline bool isEnable() const { return this->enable; }

        inline void setAble(bool able) { this->enable = able; }

        //打印某个频道
        void printChannel(Actor *player, size_t channel);

        //重置某个频道
        void resetChannel(Actor *player, size_t channel);
    };
}
#endif //TRAPDOOR_HOPPER_H

//
// Created by xhy on 2020/8/29.
//

#ifndef TRAPDOOR_HOPPER_H
#define TRAPDOOR_HOPPER_H

#include "lib/mod.h"
#include <map>
#include <array>
#include <vector>
#include "entity/Actor.h"
#include "block/Block.h"
#include "tools/noncopyable .h"
#include "trapdoor.h"
#include "commands/CommandManager.h"
#include <array>
//漏斗计数器频道
namespace mod {

    using Actor = trapdoor::Actor;
    using BlockActor = trapdoor::BlockActor;
    using BlockPos = trapdoor::BlockPos;

    class CounterChannel {
        const size_t channel; //频道号
        std::map<std::string, size_t> counterList; //数据
        size_t gameTick = 0; //游戏刻
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
    class HopperChannelManager : noncopyable {
        std::vector<CounterChannel> channels;
        bool enable = false;
    public:
        static const size_t TOTAL_CHANNEL_NUM;
        static const trapdoor::BlockType BLOCK_TYPE;

        HopperChannelManager() {
            for (int i = 0; i < 16; i++)
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

        void registerCommand(trapdoor::CommandManager &commandManager);

        void quickPrintData(trapdoor::Actor *player, trapdoor::BlockPos &pos);
    };
}
#endif //TRAPDOOR_HOPPER_H

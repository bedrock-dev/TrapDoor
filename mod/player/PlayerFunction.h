//
// Created by xhy on 2021/1/3.
//

#ifndef MOD_PLAYERFUNCTION_H
#define MOD_PLAYERFUNCTION_H

#include <map>
#include <string>
#include "entity/Actor.h"
#include "tools/noncopyable .h"
#include "graphics/BlockPos.h"
#include "block/BlockSource.h"
#include "block/CircuitComponent.h"
#include "world/Dimension.h"
#include "commands/CommandManager.h"
namespace mod {
    struct MeasureData {
        bool enableMeasure = false;
        trapdoor::BlockPos pos1;
        bool hasSetPos1 = false;
        trapdoor::BlockPos pos2;
        bool hasSetPos2 = false;

        void setPosition1(const trapdoor::BlockPos &pos, trapdoor::Actor *player);

        void setPosition2(const trapdoor::BlockPos &pos, trapdoor::Actor *player);

        void trySendDistanceInfo(trapdoor::Actor *player) const;
    };

    class PlayerFunction : noncopyable {
        std::map<std::string, bool> enableShowChunk;
        std::map<std::string, bool> enableRedstoneHelper;
        std::map<std::string, MeasureData> playerMeasureData;
        unsigned long long gameTick = 0;

        static void drawChunkBound(trapdoor::Actor *player);

    public:
        inline void setShowChunkAble(const std::string &playerName, bool able) { enableShowChunk[playerName] = able; }

        inline void
        setRedstoneHelperAble(const std::string &playerName, bool able) { enableRedstoneHelper[playerName] = able; }

        MeasureData &getMeasureData(const std::string &playerName) { return playerMeasureData[playerName]; }

        void tick();

        static void printDebugInfo(trapdoor::Actor *player);

        static void broadcastSimpleInfo(trapdoor::Actor *player);

        void printRedstoneInfo(trapdoor::Actor *player, trapdoor::BlockPos &pos);

        void registerSelfCommand(trapdoor::CommandManager &commandManager);

        static void listAllPlayers(trapdoor::Actor *player);

    };


}


#endif //MOD_PLAYERFUNCTION_H

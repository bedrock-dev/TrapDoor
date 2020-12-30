

#ifndef TRAPDOOR_ACTOR_H
#define TRAPDOOR_ACTOR_H

#include "graphics/Vec3.h"
#include <vector>
#include <string>
#include "commands/CommandNode.h"


namespace trapdoor {
    class PlayerInventory;

    class Dimension;

    class BlockSource;//玩家网络id
    struct NetworkIdentifier {
        uint64_t getHash();
    };


    class Level;

//实体对象(主要指的玩家,懒得做类型判定了)
    class Actor {
    public:
        //实体
        Vec3 *getPos();

        void getViewActor(Vec3 *vec3, float val);

        std::string getNameTag();

        void setGameMode(int mode);

        BlockSource *getBlockSource();

        void printInfo();

        int getDimensionID();

        Dimension *getDimension();

        std::string getDimensionName();

        NetworkIdentifier *getClientID();

        CMD_LEVEL getCommandLevel();

        PlayerInventory *getPlayerInventory();

        unsigned int getSelectSlot();

        Level *getLevel();
    };


/**
 * 实体标签
 * todo: 重写这个结构，因为已经知道这个东西的具体结构，因此不再需要reinterrupt了
 */
    class ActorDefinitionIdentifier {
    public:
        std::string getName();
    };

/*
 *todo 下面的一堆东西甚至没有OOP化，全部要重写
*/

    std::string actorIDtoString(char *actorID);

    std::vector<std::string> getActorText(void *actor);


//todo 这里的刷怪统计要重写，放到Spawn里面
    void sendMobInfo();

    void startSpawnCounter();

    void endSpawnerCounter();

    void spawnAnalysis(std::string &type);

    std::string getActorName(void *actor);
}
#endif

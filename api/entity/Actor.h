

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

    struct ActorUniqueID {
        int64_t uid;

        bool operator==(const ActorUniqueID &u) const {
            return this->uid == u.uid;
        }
    };

    struct ActorUniqueIDHash {
        static uint64_t mceHaseAccLong(uint64_t a1, uint64_t a2) {
            return ((a1 >> 2) + (a1 << 6) + a2 + 2654435769u) ^ a1;
        }

        static uint64_t mceHsaLongLong(uint64_t a1, uint64_t a2) {
            auto x = mceHaseAccLong(0, a1);
            return mceHaseAccLong(x, a2);
        }

        std::size_t operator()(const ActorUniqueID &key) const {
            return mceHsaLongLong(key.uid >> 32, key.uid);
        }
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

        int getDimensionID();

        Dimension *getDimension();

        std::string getDimensionName();

        NetworkIdentifier *getClientID();

        PlayerPermissionLevel getCommandLevel();

        PlayerInventory *getPlayerInventory();

        unsigned int getSelectSlot();

        BlockPos getStandPosition();

        std::string getActorId();

        Level *getLevel();

        void setNameTag(const std::string &name);
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

    std::string getActorName(void *actor);
}
#endif

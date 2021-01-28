

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

        //获取头部坐标
        Vec3 *getPos();

        //获取视角
        void getViewActor(Vec3 *vec3, float val);

        //获取头顶tag名字
        std::string getNameTag();

        //设置游戏模式
        void setGameMode(int mode);

        //获取 blocksource
        BlockSource *getBlockSource();

        //获取维度id
        int getDimensionID();

        //获取维度对象
        Dimension *getDimension();

        //获取维度名字
        std::string getDimensionName();

        //获取客户端网络id
        NetworkIdentifier *getClientID();

        //获取玩家权限等级
        PlayerPermissionLevel getCommandLevel();

        //获取玩家背包
        PlayerInventory *getPlayerInventory();

        unsigned int getSelectSlot();

        //获取站立位置
        BlockPos getStandPosition();

        //获取实体类型id
        std::string getActorId();

        //获取level对象
        Level *getLevel();

        //设置头顶的tag
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
}
#endif

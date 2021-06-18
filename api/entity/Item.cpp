//
// Created by xhy on 2020/8/29.
//

#include "Item.h"
#include <string>
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "block/Block.h"
#include "PlayerBuffer.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "tools/DirtyLogger.h"
#include "tools/CastHelper.h"
#include "Offset.h"

namespace trapdoor {
    using namespace SymHook;

    std::string ItemStackBase::getItemName() {
        std::string name;
        SYM_CALL(
                void(*)(ItemStackBase * , std::string *),
            MSSYM_MD5_6d581a35d7ad70fd364b60c3ebe93394,
                this, &name);
        return name;
    }

    int ItemStackBase::getNum() {
        return *offset_cast<char *>(this, off::ITEM_GET_NUM);
    }

//    void ItemStackBase::setNull() {
//        SYM_CALL(void(*)(ItemStackBase * ),
//                 SymHook::MSSYM_B1QA7setNullB1AE13ItemStackBaseB2AAA7UEAAXXZ,
//                 this);
//    }
}  // namespace trapdoor

using namespace SymHook;
//右键代理类
THook(
        void,
        MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z,
        void *item,
        trapdoor::ItemStackBase *itemStack,
        trapdoor::Actor *player,
        int x,
        int y,
        int z,
        unsigned int facing,
        float dx,
        float dy,
        float dz) {
    uint64_t gameTick = trapdoor::bdsMod->getTrapdoorTick();
    // L_INFO("%.2f %.2f %.2f,tick =  %llu", x, y, z, gameTick);
    trapdoor::RightClickCache targetCache{gameTick, x, y, z};

    auto &playerCache =
            trapdoor::bdsMod->getPlayerBuffer()[player->getNameTag()]
                    .rightClickCache;
    //下面用一个简单的缓存 + 判定消除重复点击
    if (playerCache != targetCache) {
        //响应右键事件
        trapdoor::BlockPos pos(x, y, z);
        const trapdoor::Vec3 vec3(dx, dy, dz);
        trapdoor::bdsMod->useOnHook(player, itemStack->getItemName(), pos,
                                    facing, vec3);
        playerCache = targetCache;
    }
    original(item, itemStack, player, x, y, z, facing, dx, dy, dz);
}

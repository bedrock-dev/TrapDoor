//
// Created by xhy on 2020/8/29.
//

#include "Item.h"
#include <string>
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "block/Block.h"
#include "PlayerBuffer.h"
#include "tools/DirtyLogger.h"
#include "tools/CastHelper.h"
#include "Offset.h"
#include "Loader.h"

namespace trapdoor {


    std::string ItemStackBase::getItemName() {
        std::string name;
        SymCall("?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"
            , void, ItemStackBase*, std::string*)(this, &name);
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


//右键代理类
THook(
        void,
        "?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEMMM@Z",
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

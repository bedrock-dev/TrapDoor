//
// Created by xhy on 2020/8/29.
//

#include "Item.h"
#include <string>
#include "common/Common.h"
#include "tools/Message.h"
#include "tools/Particle.h"
#include "tools/MessageBuilder.h"

std::string ItemStackBase::getItemName() {
    std::string name;
    SYM_CALL(
            void(*)(ItemStackBase * , std::string *),
            MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
            this, &name
    );
    return name;
}

int ItemStackBase::getNum() {
    return (int) *((unsigned char *) this + 34);
}

/**
 * minecraft:sticky_piston
 *minecraft:piston
 * minecraft:observer
 */

int getNormalState(unsigned int face, float x, float y, float z, bool isPiston) {
    unsigned flag1 = 0, flag2 = 0;
    if (face == 0 || face == 1) {
        flag1 = x + z >= 1.0f ? 1 : 0;
        flag2 = x >= z ? 1 : 0;
        int arr[4] = {4, 2, 3, 5};
        if (isPiston) {
            arr[0] = 5;
            arr[1] = 3;
            arr[2] = 2;
            arr[3] = 4;
        }
        return arr[flag1 * 2 + flag2];
    } else if (face == 2 || face == 3) {
        flag1 = x + y >= 1.0f ? 1 : 0;
        flag2 = x >= y ? 1 : 0;
        int arr[4] = {4, 0, 1, 5};
        if (isPiston) {
            arr[0] = 5;
            arr[3] = 4;
        }
        return arr[flag1 * 2 + flag2];
    } else if (face == 4 || face == 5) {
        flag1 = y + z >= 1.0f ? 1 : 0;
        flag2 = y >= z ? 1 : 0;
        int arr[4] = {0, 2, 3, 1};
        if (isPiston) {
            arr[1] = 3;
            arr[3] = 2;
        }
        return arr[flag1 * 2 + flag2];
    }
    return 0;
}

int getChestState(unsigned int face, float x, float y, float z) {
    if (face == 0 || face == 1)return getNormalState(face, x, y, z, false);
    if (face == 2 || face == 3)return x >= 0.5 ? 5 : 4;
    if (face == 4 || face == 5)return z >= 0.5 ? 3 : 2;
    return 0;
}

int getCapacitorState(unsigned int face, float x, float y, float z, bool powered) {

    if (face == 0 || face == 1) {
        int flag1 = x + z >= 1.0f ? 1 : 0;
        int flag2 = x >= z ? 1 : 0;
        int arr[4] = {3, 0, 2, 1};
        if (powered) {
            for (auto &i:arr)i += 4;
        }
        return arr[flag1 * 2 + flag2];
    } else {
        int arr[4] = {0, 2, 3, 1};
        if (powered) {
            for (auto &i:arr)i += 4;
        }
        return arr[face - 2];
    }
}

//hopper
//chest


BlockPos redStonePosCache;

THook(
        void,
        MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z,
        void *item,
        ItemStackBase *itemStack,
        Actor *player,
        int x,
        int y,
        int z,
        unsigned int facing,
        float dx,
        float dy,
        float dz
) {
    auto name = itemStack->getItemName();
    auto blockSource = player->getBlockSource();
    if (name == "Cactus") {
        auto block = blockSource->getBlock(x, y, z);
        auto blockName = block->getName();
        BlockPos pos(x, y, z);
        auto state = getNormalState(facing, dx, dy, dz, false);
        if (blockName == "minecraft:piston" || blockName == "minecraft:sticky_piston") {
            state = getNormalState(facing, dx, dy, dz, true);
        } else if (blockName == "minecraft::chest") {
            state = getChestState(facing, dx, dy, dz);
        } else if (blockName == "minecraft:unpowered_repeater" || blockName == "minecraft:unpowered_comparator") {
            state = getCapacitorState(facing, dx, dy, dz, false);
        } else if (blockName == "minecraft:powered_repeater" || blockName == "minecraft:powered_comparator") {
            state = getCapacitorState(facing, dx, dy, dz, true);
        }
        blockSource->setBlock(&pos, block->getLegacy()->tryGetStateBlock(state));
    } else if (name == "Stick") {
        //todo
//        auto block = blockSource->getBlock(x, y, z);
//        auto blockName = block->getName();
//        BlockPos pos(x, y, z);
//        if (pos != redStonePosCache) {
//            auto component = globalCircuitSceneGraph->getBaseCircuitComponent(&pos);
//            if (component) {
//                //  info("s: %d", component->getStrength());
//                component->basePrint();
//                //中继器特判
//                if (blockName == "minecraft:unpowered_repeater" || blockName == "minecraft:powered_repeater") {
//                    component->printRepeater();
//                    //火把特判
//                } else if (blockName == "minecraft:redstone_torch" || blockName == "minecraft:unlit_redstone_torch") {
//                    component->printTorch(pos);
//                }
//            }
//            redStonePosCache = pos;
//        }
    }
    original(item, itemStack, player, x, y, z, facing, dx, dy, dz);
}


//
// Created by xhy on 2021/2/3.
//

#include "VanillaBlockType.h"
#include "BDSMod.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    namespace {
        std::unordered_map<trapdoor::BlockType, BlockLegacy *> &getBlockMap() {
            static std::unordered_map<trapdoor::BlockType, BlockLegacy *> map;
            return map;
        }
    }

    trapdoor::BlockLegacy *getBlockLegacyByID(BlockType type) {
        auto iter = getBlockMap().find(type);
        if (iter != getBlockMap().end()) {
            return iter->second;
        }
        return getBlockMap()[AIR];
    }

    void initBlockMap() {
        L_DEBUG("init block map");
        std::function < bool(trapdoor::BlockLegacy & b) > function(
                [&](trapdoor::BlockLegacy &l) {
                    getBlockMap()[l.getBlockID()] = &l;
                    return true;
                });
        SymCall("?forEachBlock@BlockTypeRegistry@@SAXV?$function@$$A6A_NAEBVBlockLegacy@@@Z@std@@@Z", void, const std::function < bool(BlockLegacy&)> *)(&function);
    }

    trapdoor::Block *getBlockByID(BlockType type, unsigned short variant) {
        auto *blockLegacy = getBlockLegacyByID(type);
        return blockLegacy->tryGetStateBlock(variant);
    }
}
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
        L_INFO("init block map");
        using namespace SymHook;
        std::function < bool(trapdoor::BlockLegacy & b) > function(
                [&](trapdoor::BlockLegacy &l) {
                    getBlockMap()[l.getBlockID()] = &l;
                    return true;
                });
        SYM_CALL(
                void(*)(const std::function < bool(BlockLegacy &)> *),
                MSSYM_B1QE12forEachBlockB1AE17BlockTypeRegistryB2AAA4SAXVB2QDA8functionB3ADDA3A6AB1UE16NAEBVBlockLegacyB3AAAA1ZB1AA3stdB3AAAA1Z,
                &function
        );
    }

    trapdoor::Block *getBlockByID(BlockType type, unsigned short variant) {
        auto *blockLegacy = getBlockLegacyByID(type);
        return blockLegacy->tryGetStateBlock(variant);
    }

}
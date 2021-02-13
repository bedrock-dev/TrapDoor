//
// Created by xhy on 2021/1/3.
//

#include "BlockRotationHelper.h"
#include "block/Block.h"
#include "block/BlockSource.h"
#include "graphics/BlockPos.h"
#include "block/VanillaBlockType.h"

namespace mod {
    //我有点后悔搞个单独的类了
    void BlockRotationHelper::rotate(trapdoor::BlockPos &pos,
                                     trapdoor::BlockSource *blockSource) const {
        using trapdoor::BlockSource;
        if (!this->enable)
            return;
        auto block = blockSource->getBlock(pos);
        auto air = trapdoor::getBlockByID(trapdoor::AIR);
        auto variant = block->getVariant();
        auto name = block->getName();
        if (name.find("slab") != std::string::npos) {
            auto newState = (variant + 8) % 16;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("stonecutter_block") != std::string::npos) {
            auto newState = 0;
            if (variant < 4)
                newState = 4;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("bell") != std::string::npos) {
            auto newState = (variant + 1) % 16;
            blockSource->setBlock(&pos, air);
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("stairs") != std::string::npos) {
            auto newState = (variant + 1) % 8;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("sea") == std::string::npos &&
                   name.find("lantern") != std::string::npos) {
            auto newState = (variant + 1) % 2;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("torch") != std::string::npos) {
            auto newState = (variant + 1) % 5;
            blockSource->setBlock(&pos, air);
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
            blockSource->updateNeighbors(&pos);
        } else if (name.find("cake") != std::string::npos) {
            auto newState = (variant + 1) % 7;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("grindstone") != std::string::npos) {
            auto newState = (variant + 1) % 12;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("_rail") != std::string::npos ||
                   name.find("dropper") != std::string::npos ||
                   name.find("dispenser") != std::string::npos ||
                   name.find("observer") != std::string::npos ||
                   name.find("piston") != std::string::npos ||
                   name.find("lever") != std::string::npos ||
                   name.find("button") != std::string::npos ||
                   name.find("rod") != std::string::npos ||
                   name.find("barrel") != std::string::npos ||
                   name.find("glazed_terracotta") != std::string::npos) {
            auto newState = (variant % 8 + 1) % 6 + (variant / 8) * 8;
            blockSource->setBlock(&pos, air);
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            //blockSource->setBlock(&pos, blockSource->getBlock(pos + trapdoor::BlockPos(0, 1, 0)));
            blockSource->setBlock(&pos, newBlock);
            blockSource->updateNeighbors(&pos);
        } else if (name.find("rail") != std::string::npos) {
            auto newState = (variant + 1) % 10;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, air);
            blockSource->setBlock(&pos, newBlock);
            blockSource->updateNeighbors(&pos);
        } else if ((name.find("log") != std::string::npos &&
                    name.find("stripped") != std::string::npos) ||
                   name.find("basalt") != std::string::npos ||
                   name.find("crimson_stem") != std::string::npos ||
                   name.find("warped_stem") != std::string::npos) {
            auto newState = (variant + 1) % 3;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("log") != std::string::npos) {
            auto newState = (variant + 4) % 16;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("powered") != std::string::npos ||
                   name.find("anvil") != std::string::npos ||
                   name.find("lectern") != std::string::npos ||
                   name.find("_door") != std::string::npos ||
                   name.find("loom") != std::string::npos) {
            auto newState = (variant % 4 + 1) % 4 + (variant / 4) * 4;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, air);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("trapdoor") != std::string::npos) {
            auto newState = (variant % 8 + 1) % 8 + (variant / 8) * 8;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, air);
            blockSource->setBlock(&pos, newBlock);
        } else if (name.find("hopper") != std::string::npos) {
            auto newState = (variant % 8 + 1) % 6 + (variant / 8) * 8;
            if (newState % 8 == 1)
                newState += 1;
            auto newBlock = block->getLegacy()->tryGetStateBlock(newState);
            blockSource->setBlock(&pos, air);
            blockSource->setBlock(&pos, newBlock);
        }
    }
}  // namespace mod

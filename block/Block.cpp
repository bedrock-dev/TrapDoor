//
// Created by xhy on 2020/8/26.
//
#include "Block.h"
#include "tools/Message.h"
#include "common/Vec3.h"
#include "common/BlockPos.h"
#include "tools/MathTool.h"

using namespace SymHook;






//namespace block {
//    std::vector<Vec3> posCache;
//}

/**
 * Hook 用铲子右击方块的函数
 * 老实说这里的功能蛮费的
 */


//THook(
//        void,
//        MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z,
//        void *a1,
//        void *a2,
//        void *hopperBlockActor,
//        int *blockPos,
//        float a4,
//        float a5,
//        float a6
//) {
//    Vec3 pos(blockPos[0], blockPos[1], blockPos[2]);
//    BlockPos bp(blockPos[0], blockPos[1], blockPos[2]);
//    //printf("%d %d %d\commandMap", blockPos[0], blockPos[1], blockPos[2]);
//    //   villageHelper.POIBelong(&bp);
//    if (enableMarkPos) {
//        if (block::posCache.empty()) {
//            block::posCache.emplace_back(pos);
//            block::posCache.emplace_back(pos);
//        } else {
//            block::posCache[0] = block::posCache[1];
//            block::posCache[1] = pos;
//        }
//        if (block::posCache[0] != block::posCache[1]) {
//            gamePrintf("(%d,%d,%d),(%d,%d,%d):%.2f(%.2f),%d(%d)\n",
//                       (int) block::posCache[0].x,
//                       (int) block::posCache[0].y,
//                       (int) block::posCache[0].z,
//                       (int) block::posCache[1].x,
//                       (int) block::posCache[1].y,
//                       (int) block::posCache[1].z,
//                       math::distance(block::posCache[0], block::posCache[1], false, true),
//                       math::distance(block::posCache[0], block::posCache[1], false, false),
//                       (int) math::distance(block::posCache[0], block::posCache[1], true, true),
//                       (int) math::distance(block::posCache[0], block::posCache[1], true, false)
//            );
//            std::string str = "minecraft:redstone_wire_dust_particle";
//        }
//    } else {
//        original(a1, a2, hopperBlockActor, blockPos, a4, a5, a6);
//    }
//}
//
//
//
////海绵放置
//THook(
//        void,
//        MSSYM_B1QA7onPlaceB1AE11SpongeBlockB2AAE20UEBAXAEAVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z,
//        void *b,
//        void *bs,
//        BlockPos * blockPos
//) {
//    void *block = SYM_CALL(
//            void* (*)(void * , int, int, int),
//            MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z, globalBlockSource,
//            blockPos->x, blockPos->y - 1, blockPos->z
//    );
//    if (block) {
//        for (int i = 0; i < 10; i++) {
//            BlockPos p(blockPos->x, blockPos->y + i, blockPos->z);

//        }
//    } else {
//        gamePrintf("can't get block");
//    }
//
//}

#include <vector>

BlockLegacy *Block::getLegacy() {
    return SYM_CALL(
            BlockLegacy*(*)(Block * block),
            MSSYM_B1QE14getLegacyBlockB1AA5BlockB2AAE19QEBAAEBVBlockLegacyB2AAA2XZ,
            this
    );
}

std::string Block::getName() {
    std::string debugStr;
    SYM_CALL(
            void(*)(void * block, std::string &),
            MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
            this, debugStr);
    //remove "name: "
    return debugStr.erase(0, 6);
}

bool Block::isNotAir() {
    return this->getName() != "minecraft:air";
}


std::string BlockLegacy::getDebugText() {
    std::vector<std::string> vector;
    SYM_CALL(
            void(*)(BlockLegacy * , std::vector<std::string> &),
            MSSYM_MD5_794b421b4bf67101f7418cd0d78bad83,
            this, vector
    );
    int i = 0;
    for (const auto &str:vector) {
        printf("%d: %s ", i, str.c_str());
        ++i;
    }
    printf("\n");
    return std::string("text");
}

Block *BlockSource::getBlock(int x, int y, int z) {
    return SYM_CALL(
            Block* (*)(void * , int, int, int),
            MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z, this,
            x, y, z
    );
}

Block *BlockSource::getBlock(const BlockPos &blockPos) {
    return getBlock(blockPos.x, blockPos.y, blockPos.z);
}

void BlockSource::setBlock(BlockPos *blockPos, Block *block) {
    SYM_CALL(
            void(*)(void * , BlockPos *, void *, int, void *),
            MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAE26HPEBUActorBlockSyncMessageB3AAAA1Z,
            this, blockPos, block, 0, nullptr
    );
    this->updateNeighborsAt(blockPos);
}

void BlockSource::updateNeighborsAt(const BlockPos *pos) {
//    dbg("update");
    SYM_CALL(
            void(*)(BlockSource * self,const BlockPos *pos),
            MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
            this, pos
    );
}

THook(
        void,
        MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
        BlockSource *self, const BlockPos *pos
) {
    original(self, pos);
}
//explosion enable
THook(
        void,
        MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ,
        void * exp
) {
    if (enableExplosion) {
        original(exp);
    }
}

int BaseCircuitComponent::getStrength() {
    return *((uint32_t *) this + 13);
}

int BaseCircuitComponent::getVar2() {
    return *((uint64_t *) this + 2);

}

void BaseCircuitComponent::printSource() {
    auto begin = (uint32_t *) *((uint64_t *) this + 1);
    auto end = (uint32_t *) *((uint64_t *) this + 2);
    int num = 0;

    for (; begin != end; begin += 8) {
        auto val = (int *) begin;
        BlockPos pos = BlockPos(val[3], val[4], val[5]);
        auto comp = globalCircuitSceneGraph->getBaseCircuitComponent(&pos);
        if (comp) {
            printf(" [%d %d %d]-> %d\n", pos.x, pos.y, pos.z, comp->getStrength());
        }
        num++;
    }
    gamePrintf("\nsignal:%d source: %d\n", getStrength(), num);
}

BaseCircuitComponent *CircuitSceneGraph::getBaseCircuitComponent(BlockPos *pos) {
    return SYM_CALL(
            BaseCircuitComponent*(*)(CircuitSceneGraph * graph,const BlockPos *pos),
            MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
            this, pos
    );
}

THook(
        BaseCircuitComponent *,
        MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
        CircuitSceneGraph *graph,
        BlockPos * pos
) {
    if (graph && !globalCircuitSceneGraph) {
        dbg("init graph");
        globalCircuitSceneGraph = graph;
    }
    return original(graph, pos);
}


//
// Created by xhy on 2020/8/26.
//
#include "Block.h"
#include "tools/Message.h"
#include "common/Vec3.h"
#include "common/BlockPos.h"
#include "tools/MathTool.h"

using namespace SymHook;

#include "tools/Particle.h"

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

Block *BlockLegacy::tryGetStateBlock(unsigned short state) {
    return SYM_CALL(
            Block *(*)(BlockLegacy * , unsigned short),
            MSSYM_B1QE25tryGetStateFromLegacyDataB1AE11BlockLegacyB2AAE13QEBAPEBVBlockB2AAA1GB1AA1Z,
            this, state
    );
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
            this, blockPos, block, 3, nullptr
    );
    // this->updateNeighborsAt(blockPos);
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

void BaseCircuitComponent::basePrint() {
    auto begin = (uint32_t *) *((uint64_t *) this + 1);
    auto end = (uint32_t *) *((uint64_t *) this + 2);
    int num = 0;
    std::string particleType = "minecraft:silverfish_grief_emitter";
    Vec3 vec3{};
    for (; begin != end; begin += 8) {
        auto val = (int *) begin;
        BlockPos pos = BlockPos(val[3], val[4], val[5]);
        auto comp = globalCircuitSceneGraph->getBaseCircuitComponent(&pos);
        if (comp) {
           // info(" (%d %d %d) <=> %d\n", pos.x, pos.y, pos.z, comp->getStrength());
            vec3.x = (float) pos.x;
            vec3.y = (float) pos.y + 0.7f;
            vec3.z = (float) pos.z;
            spawnParticle(vec3, particleType);
        }
        num++;
    }
}

int BaseCircuitComponent::getPowerCount() {
    return (int) *((int *) this + 20);
}

void BaseCircuitComponent::setAcceptHalfPulse() {
    *((char *) this + 67) = 1;
}

int BaseCircuitComponent::getAcceptHalfPulse() {
    return (int) *((char *) this + 67);
}

void BaseCircuitComponent::printRepeater() {
    int *ptr = (int *) this;
//    info("repeater: %d %d %d %d  s: %d", ptr[21], ptr[20], ptr[19], ptr[18], ((char *) this)[96]);
}

void BaseCircuitComponent::printTorch(BlockPos pos) {
    int selfPowerCount = (int) *((int *) this + 20);
    auto strength = (char) *((char *) this + 84);
    bool flag;
    int signal = SYM_CALL(
            int(*)(BaseCircuitComponent * ,const BlockPos *pos,void *circuitSystem,bool *),
            MSSYM_B1QE21FindStrongestStrengthB1AE22RedstoneTorchCapacitorB2AAE17AEAAHAEBVBlockPosB2AAE17AEAVCircuitSystemB2AAA3AEAB1UA1NB1AA1Z,
            this, &pos,
            globalCircuitSystem,
            &flag
    );
//    info("torch: bc: %d s: %d hp: %d", selfPowerCount, strength, getHalfPulse());
 //   info("%d %d", signal, flag);
}

int BaseCircuitComponent::getHalfPulse() {
    return (int) *((char *) this + 85);
}


BaseCircuitComponent *CircuitSceneGraph::getBaseCircuitComponent(BlockPos *pos) {
    return SYM_CALL(
            BaseCircuitComponent*(*)(CircuitSceneGraph * graph,const BlockPos *pos),
            MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
            this, pos
    );
}

//
//THook(
//        int,
//        MSSYM_B1QE21FindStrongestStrengthB1AE22RedstoneTorchCapacitorB2AAE17AEAAHAEBVBlockPosB2AAE17AEAVCircuitSystemB2AAA3AEAB1UA1NB1AA1Z,
//        BaseCircuitComponent *component,
//        BlockPos *pos,
//        void *circuitSystem,
//        bool * flag
//) {
//    if (circuitSystem != globalCircuitSystem) {
//        dbg("init circuitSystem");
//        globalCircuitSystem = circuitSystem;
//    }
//    int strength = original(component, pos, circuitSystem, flag);
//    if (tick::tickStatus == TickStatus::Frozen || tick::tickStatus == TickStatus::Forward) {
//        printf("[%d %d %d]: signal: %d, flag: %d \n", pos->x, pos->y, pos->z, strength, *flag);
//    }
//    return strength;
//}

THook(
        BaseCircuitComponent *,
        MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
        CircuitSceneGraph *graph,
        BlockPos * pos
) {
    if (graph && !globalCircuitSceneGraph) {
        globalCircuitSceneGraph = graph;
    }
    return original(graph, pos);
}

//
//THook(
//        void,
//        MSSYM_B1QE13setExtraBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAA1HB1AA1Z,
//        BlockSource *source,
//        BlockPos *pos,
//        Block *block,
//        int flag
//) {
//    original(source, pos, block, flag);
//    //no origin call()
//}

//
//THook(
//        void,
//        MSSYM_B2QUA7setSeedB1AA6RandomB1AA4CoreB2AAA6AEAAXIB1AA1Z,
//        void *random,
//        unsigned int seed
//) {
//    if (globalPlayer) {
//        printf("a: %p  seed: %u\n", random, seed);
//    }
//    if ((uint64_t) random == playerRand) {
//        return original(random, particleViewDistance);
//    } else {
//        return original(random, seed);
//    }
//}
//
//THook(
//        uint32_t,
//        MSSYM_B2QUE12genRandInt32B1AA6RandomB1AA4CoreB2AAA7AEAAIXZ,
//        void * random
//) {
//    return original(random);
//}

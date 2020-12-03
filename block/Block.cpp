//
// Created by xhy on 2020/8/26.
//
#include "Block.h"
#include "tools/Message.h"
#include "common/Vec3.h"
#include "common/BlockPos.h"
#include "tools/MathTool.h"
#include "level/Biome.h"
#include "tick/GameTick.h"

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

int Block::getVariant() {
    //? asddddddddd
    //! from BlockLegacy::getVariant(BlockLegacy *this, char *a2)
    return reinterpret_cast<char *>(this)[8];
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

Biome *BlockSource::getBiome(const BlockPos *pos) {
    return
            SYM_CALL(
                    Biome*(*)(BlockSource * , const BlockPos *),
                    MSSYM_B1QA8getBiomeB1AE11BlockSourceB2AAE13QEAAAEAVBiomeB2AAE12AEBVBlockPosB3AAAA1Z,
                    this,
                    pos
            );
}

void BlockSource::updateNeighbors(BlockPos pos) {
    auto blockList = pos.getNeighbourPos();
    for (auto &p:blockList) {
        this->updateNeighborsAt(&p);
    }
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
//    auto begin = (uint32_t *) *((uint64_t *) this + 1);
//    auto end = (uint32_t *) *((uint64_t *) this + 2);
//    int num = 0;
//    std::string particleType = "minecraft:silverfish_grief_emitter";
//    Vec3 vec3{};
//    for (; begin != end; begin += 8) {
//        auto val = (int *) begin;
//        BlockPos pos = BlockPos(val[3], val[4], val[5]);
//        auto comp = globalCircuitSceneGraph->getBaseCircuitComponent(&pos);
//        if (comp) {
//            // info(" (%d %d %d) <=> %d\n", pos.x, pos.y, pos.z, comp->getStrength());
//            vec3.x = (float) pos.x;
//            vec3.y = (float) pos.y + 0.7f;
//            vec3.z = (float) pos.z;
//            spawnParticle(vec3, particleType);
//        }
//        num++;
//    }
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


THook(
        BaseCircuitComponent *,
        MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
        CircuitSceneGraph *graph,
        BlockPos * pos
) {
//    if (graph && !globalCircuitSceneGraph) {
//        globalCircuitSceneGraph = graph;
//    }
    return original(graph, pos);
}


void findMUl(const std::vector<std::pair<int, int>> &list, long long int maxDis2) {
    size_t length = list.size();
    for (int i = 0; i < length - 1; ++i) {
        for (int j = i + 1; j < length; j++) {
            long long int dx = list[i].first - list[j].first;
            long long int dy = list[i].second - list[j].second;
            long long int d2 = dx * dx + dy * dy;
            if (d2 <= maxDis2) {
                printf("p1 :[%d ~ %d]       p2:[%d %d]  ==> d: %.2f\n", list[i].first, list[i].second, list[j].first,
                       list[j].second, sqrt(d2));
            }
        }
    }

}


bool hasFindRandomScattered = false;

THook(
        bool,
        MSSYM_B1QE14isFeatureChunkB1AE27RandomScatteredLargeFeatureB2AAA4MEAAB1UE16NAEBVBiomeSourceB2AAE10AEAVRandomB2AAE12AEBVChunkPosB2AAA1IB1AA1Z,
        int32_t *structure,
        char *biomeSource,
        void *rand,
        ChunkPos *pos,
        unsigned int v3
) {

    bool result = original(structure, biomeSource, rand, pos, v3);
    if (hasFindRandomScattered) return result;
    printf("begin finder randomScattered\n");
    int range = 1000;
    int blockSize = range / 5 + 1;
    ChunkPos p = {0, 0};
    std::vector<std::pair<int, int>> list;
    for (int i = -range; i < range; ++i) {
        for (int j = -range; j < range; ++j) {
            p.x = i;
            p.z = j;
            if (original(structure, biomeSource, rand, &p, v3)) {
                Biome *biome = SYM_CALL(
                        Biome*(*)(void * , int, int),
                        MSSYM_B1QA8getBiomeB1AE16LayerBiomeSourceB2AAE13UEBAPEBVBiomeB2AAA2HHB1AA1Z,
                        biomeSource,
                        p.x * 16, p.z * 16
                );
                printf("(/tp %d ~ %d) == %d %s\n", 16 * p.x, 16 * p.z, biome->getBiomeType(), biome->getBiomeName().c_str());
                //if (biome->getBiomeType() == 15) {
                list.emplace_back(i * 16, j * 16);
                //}
            }
        }
    }

    size_t length = list.size();
    printf("%zu find begin cal ScatteredFeature distance...\n", length);
    findMUl(list, 40000);
    hasFindRandomScattered = true;
    printf("finish finder random Scattered\n");
    return result;
}




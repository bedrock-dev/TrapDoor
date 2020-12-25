//
// Created by xhy on 2020/8/26.
//
#include <vector>
#include "Block.h"
#include "tools/Message.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "block/BlockLegacy.h"

namespace trapdoor {
    using namespace SymHook;

    //获取方块legacy
    BlockLegacy *Block::getLegacy() {
        return SYM_CALL(
                BlockLegacy * (*)(Block * block),
                MSSYM_B1QE14getLegacyBlockB1AA5BlockB2AAE19QEBAAEBVBlockLegacyB2AAA2XZ,
                this
        );
    }

    //获取方块名字
    std::string Block::getName() {
        std::string debugStr;
        SYM_CALL(
                void(*)(void * block, std::string &),
                MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
                this, debugStr);
        //remove "name: "
        return debugStr.erase(0, 6);
    }


    //是否是空气
    bool Block::isAir() {
        return this->getName() == "minecraft:air";
    }

    //获取特殊值
    int Block::getVariant() {
        //! from BlockLegacy::getVariant(BlockLegacy *this, char *a2)
        return reinterpret_cast<char *>(this)[8];
    }

    //获取能量等级
    int BaseCircuitComponent::getStrength() {
        return *((uint32_t *) this + 13);
    }


    int BaseCircuitComponent::getVar2() {
        return *((uint64_t *) this + 2);

    }

    //打印信号源等信息
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

    //获取火把的燃烧情况
    int BaseCircuitComponent::getPowerCount() {
        return (int) *((int *) this + 20);
    }

//    //是否接受半脉冲
//    void BaseCircuitComponent::setAcceptHalfPulse() {
//        *((char *) this + 67) = 1;
//    }


    //是否接受半脉冲
    int BaseCircuitComponent::getAcceptHalfPulse() {
        return (int) *((char *) this + 67);
    }

    //打印中继器相关信息
    void BaseCircuitComponent::printRepeater() {
        int *ptr = (int *) this;
//    info("repeater: %d %d %d %d  s: %d", ptr[21], ptr[20], ptr[19], ptr[18], ((char *) this)[96]);
    }

    //打印火把相关信息
    void BaseCircuitComponent::printTorch(BlockPos pos) {
        int selfPowerCount = (int) *((int *) this + 20);
        auto strength = (char) *((char *) this + 84);
        bool flag;
//    int signal = SYM_CALL(
//            int(*)(BaseCircuitComponent * ,const BlockPos *pos,void *circuitSystem,bool *),
//            MSSYM_B1QE21FindStrongestStrengthB1AE22RedstoneTorchCapacitorB2AAE17AEAAHAEBVBlockPosB2AAE17AEAVCircuitSystemB2AAA3AEAB1UA1NB1AA1Z,
//            this, &pos,
//            globalCircuitSystem,
//            &flag
//    );
//    info("torch: bc: %d s: %d hp: %d", selfPowerCount, strength, getHalfPulse());
        //   info("%d %d", signal, flag);
    }


    //是否接受半脉冲
    int BaseCircuitComponent::getHalfPulse() {
        return (int) *((char *) this + 85);
    }


    //从电路图中获取电路组件
    BaseCircuitComponent *CircuitSceneGraph::getBaseCircuitComponent(BlockPos *pos) {
        return SYM_CALL(
                BaseCircuitComponent * (*)(CircuitSceneGraph * graph,
                const BlockPos *pos),
                MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
                this, pos
        );
    }


    //初始化电路图
    THook(
            BaseCircuitComponent
            *,
            MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
            CircuitSceneGraph *graph,
            BlockPos
            * pos
    ) {
//    if (graph && !globalCircuitSceneGraph) {
//        globalCircuitSceneGraph = graph;
//    }
        return original(graph, pos);
    }


    //获取方块实体的位置
    BlockPos *BlockActor::getPosition() {
        return reinterpret_cast<BlockPos *>(reinterpret_cast<VA>(this) + 44);
    }


    //获取方块实体内的方块对象
    Block *BlockActor::getBlock() {
        return *reinterpret_cast<Block **>(reinterpret_cast<VA>(this) + 16);
    }
}

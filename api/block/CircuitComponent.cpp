//
// Created by xhy on 2021/1/20.
//

#include "lib/mod.h"
#include "lib/SymHook.h"
#include "CircuitComponent.h"
#include "tools/DirtyLogger.h"
#include "graphics/Vec3.h"
#include "graphics/Particle.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"

namespace trapdoor {

    //获取能量等级
    int BaseCircuitComponent::getStrength() {
        return *((uint32_t *) this + 13);
    }


    int BaseCircuitComponent::getVar2() {
        return *((uint64_t *) this + 2);

    }

    //打印信号源等信息
    void BaseCircuitComponent::basePrint(CircuitSceneGraph *graph, trapdoor::Actor *player) {
        MessageBuilder builder;
        builder.text("Signal: ").num(this->getStrength());
        auto begin = (uint32_t *) *((uint64_t *) this + 1);
        auto end = (uint32_t *) *((uint64_t *) this + 2);
        int num = 0;
        std::string particleType = "minecraft:silverfish_grief_emitter";
        trapdoor::Vec3 vec3{};
        for (; begin != end; begin += 8) {
            auto val = (int *) begin;
            BlockPos pos = BlockPos(val[3], val[4], val[5]);
            auto comp = graph->getBaseCircuitComponent(&pos);
            if (comp) {
                builder.text("\n - ").pos(pos).text(" <==> ").num(comp->getStrength());
                vec3.x = (float) pos.x + 0.5f;
                vec3.y = (float) pos.y + 0.7f;
                vec3.z = (float) pos.z + 0.5f;
                spawnParticle(vec3, particleType, player->getDimensionID());
            }
            num++;
        }
        builder.send(player);
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
        using namespace SymHook;
        return SYM_CALL(
                BaseCircuitComponent * (*)(CircuitSceneGraph * graph,
                const BlockPos *pos),
                MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
                this, pos
        );
    }
}

using namespace SymHook;
//初始化电路图
//这个函数没用了
THook(
        trapdoor::BaseCircuitComponent
        *,
        MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z,
        trapdoor::CircuitSceneGraph *graph,
        trapdoor::BlockPos * pos
) {
    return original(graph, pos);
}

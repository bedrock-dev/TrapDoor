//
// Created by xhy on 2021/1/20.
//


#include "CircuitComponent.h"
#include "tools/DirtyLogger.h"
#include "graphics/Vec3.h"
#include "graphics/Particle.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "CastHelper.h"
#include "BlockSource.h"
#include "Offset.h"
#include "lib/Loader.h"
namespace trapdoor {

    //获取能量等级
    int BaseCircuitComponent::getStrength() {
        return *offset_cast<int *>(this, off::BASECIRCUITCOMPONENT_GET_STRENGTH);
    }


    //打印信号源等信息
    void BaseCircuitComponent::basePrint(CircuitSceneGraph *graph, trapdoor::Actor *player) {
        MessageBuilder builder;
        std::string stringBuilder;
        stringBuilder += trapdoor::format("Signal " C_INT, this->getStrength());
        builder.text("Signal: ").num(this->getStrength());
        //todo rewrite
        auto begin = (uint32_t *) *((uint64_t *) this + off::BASECIRCUITCOMPONENT_SOURCE_RANGE.first);
        auto end = (uint32_t *) *((uint64_t *) this + off::BASECIRCUITCOMPONENT_SOURCE_RANGE.second);
        int num = 0;
        std::string particleType = "minecraft:silverfish_grief_emitter";
        trapdoor::Vec3 vec3{};
        for (; begin != end; begin += 8) {
            auto val = (int *) begin;
            BlockPos pos = BlockPos(val[3], val[4], val[5]);
            auto comp = graph->getBaseCircuitComponent(&pos);
            if (comp) {
                stringBuilder += trapdoor::format("\n - " C_POS " <==> " C_INT, pos.x, pos.y, pos.z,
                                                  comp->getStrength());
                vec3.x = (float) pos.x + 0.5f;
                vec3.y = (float) pos.y + 0.7f;
                vec3.z = (float) pos.z + 0.5f;
                spawnParticle(vec3, particleType, player->getDimensionID());
            }
            num++;
        }
        trapdoor::info(player, stringBuilder);
    }

    //从电路图中获取电路组件
    BaseCircuitComponent *CircuitSceneGraph::getBaseCircuitComponent(BlockPos *pos) {
        return SymCall("?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z", BaseCircuitComponent*, CircuitSceneGraph * ,
            const BlockPos * )(this, pos);
    }
}



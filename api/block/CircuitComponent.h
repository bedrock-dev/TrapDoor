//
// Created by xhy on 2021/1/20.
//

#ifndef MOD_CIRCUITCOMPONENT_H
#define MOD_CIRCUITCOMPONENT_H

#include "graphics/BlockPos.h"
#include "entity/Actor.h"
namespace trapdoor {
    class CircuitSceneGraph;

    class BaseCircuitComponent {
    public:
        int getStrength();

        int getVar2();

        int getPowerCount();

        int getAcceptHalfPulse();

        int getHalfPulse();

        void basePrint(CircuitSceneGraph *graph, trapdoor::Actor *player);

        void printRepeater();

        void printTorch(BlockPos blockPos);
    };

    //红石电路图组件
    class CircuitSceneGraph {
    public:
        BaseCircuitComponent *getBaseCircuitComponent(BlockPos *pos);
    };
}

#endif //MOD_CIRCUITCOMPONENT_H

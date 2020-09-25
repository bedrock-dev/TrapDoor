//
// Created by xhy on 2020/9/9.
//

#include "Redstone.h"
#include "../common/Common.h"
#include "../lib/pch.h"
#include "../lib/SymHook.h"
#include "block/Block.h"
#include "tick/Tick.h"

using namespace SymHook;
//
//THook(
//        void,
//        MSSYM_B1QE11cacheValuesB1AE20TransporterComponentB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z,
//        BaseCircuitComponent *self,
//        void *circuitSystem,
//        BlockPos * pos
//) {
//    std::string s = pos->toString() + "[ + ] TransporterComponent ";
//    if (tick::tickStatus != TickStatus::Normal) {
//        s += std::to_string(self->getStrength());
//        s += " -> ";
//    }
//    original(self, circuitSystem, pos);
//    if (tick::tickStatus != TickStatus::Normal) {
//        auto newVal = self->getStrength();
//        s += std::to_string(newVal);
//        dbg(s);
//    }
//}
//
//
////中继器
//THook(
//        void,
//        MSSYM_B1QE11cacheValuesB1AE17RepeaterCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z,
//        BaseCircuitComponent *self,
//        void *circuitSystem,
//        BlockPos * pos
//) {
//    std::string s = pos->toString() + " [ - ] RepeaterCapacitor ";
//    if (tick::tickStatus != TickStatus::Normal) {
//        s += std::to_string(self->getStrength());
//        s += " -> ";
//    }
//    original(self, circuitSystem, pos);
//    if (tick::tickStatus != TickStatus::Normal) {
//        auto newVal = self->getStrength();
//        s += std::to_string(newVal);
//        dbg(s);
//    }
//}
//
//THook(
//        void,
//        MSSYM_B1QE11cacheValuesB1AE22RedstoneTorchCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z,
//        BaseCircuitComponent *self,
//        void *circuitSystem,
//        BlockPos * pos
//) {
//    std::string s = pos->toString() + " [ i ] RedstoneTorchCapacitor ";
//    if (tick::tickStatus != TickStatus::Normal) {
//        s += std::to_string(self->getStrength());
//        s += " -> ";
//    }
//    original(self, circuitSystem, pos);
//    if (tick::tickStatus != TickStatus::Normal) {
//        auto newVal = self->getStrength();
//        s += std::to_string(newVal);
//        dbg(s);
//    }
//}
//THook(
//        void,
//        MSSYM_B1QE11cacheValuesB1AE19ComparatorCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z,
//        BaseCircuitComponent *self,
//        void *circuitSystem,
//        BlockPos * pos
//) {
//    std::string s = pos->toString() + " [ > ] ComparatorCapacitor ";
//    if (tick::tickStatus != TickStatus::Normal) {
//        s += std::to_string(self->getStrength());
//        s += " -> ";
//    }
//    original(self, circuitSystem, pos);
//    if (tick::tickStatus != TickStatus::Normal) {
//        auto newVal = self->getStrength();
//        s += std::to_string(newVal);
//        dbg(s);
//    }
//}

//THook(
//        bool,
//        MSSYM_B1QA8evaluateB1AE20TransporterComponentB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z,
//        BaseCircuitComponent *self,
//        void *circuitSystem,
//        BlockPos * pos
//) {
//    std::string s = pos->toString() + "trans evaluate";
//    if (tick::tickStatus != TickStatus::Normal) {
//        s += std::to_string(self->getStrength());
//        s += " -> ";
//    }
//    auto i = original(self, circuitSystem, pos);
//    if (tick::tickStatus != TickStatus::Normal) {
//        auto newVal = self->getStrength();
//        s += std::to_string(newVal);
//        dbg(s);
//    }
//    return i;
//
//    return original(self, circuitSystem, pos);
//}

//THook(
//        bool,
//        MSSYM_B1QA8evaluateB1AE17ConsumerComponentB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z,
//        BaseCircuitComponent *self,
//        void *circuitSystem,
//        BlockPos * pos
//) {
//    std::string s = pos->toString() + "consumer evaluate ";
//    if (tick::tickStatus != TickStatus::Normal) {
//        s += std::to_string(self->getStrength());
//        s += " -> ";
//    }
//    auto i = original(self, circuitSystem, pos);
//    if (tick::tickStatus != TickStatus::Normal) {
//        auto newVal = self->getStrength();
//        s += std::to_string(newVal);
//        dbg(s);
//    }
//    return i;
//}

THook(
        void, MSSYM_B1QA8evaluateB1AE13CircuitSystemB2AAE20QEAAXPEAVBlockSourceB3AAAA1Z,
        void *self,
        BlockSource * bs
) {
    if (tick::tickStatus != TickStatus::Normal) {
        dbg("redstone tick");
    }
    original(self, bs);
}



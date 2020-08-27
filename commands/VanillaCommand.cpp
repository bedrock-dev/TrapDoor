//
// Created by xhy on 2020/8/27.
//
/*
 * useless code
 */
#include "VanillaCommand.h"
#include "lib/SymHook.h"
#include "tools/Message.h"

using namespace SymHook;
size_t fillCloneRange = 65535;

void resetFillCloneRange() {
    fillCloneRange = 65535;
}

void setFillCloneRange(size_t num) {
    if (num <= 524288 && num > 0) {
        fillCloneRange = num;
        dbg(fillCloneRange);
        info("set range successful");
    } else {
        error("invalid range require[0 524288]");
    }
}

THook(
        bool,
        MSSYM_B1QE10validRangeB1AA7CommandB2AAA2SAB1UE21NHHHAEAVCommandOutputB3AAAA1Z,
        void *self,
        int flag,
        int range,
        void * output
) {
    dbg(range);
    if (range == 65535) {
        //fill and clone command
        dbg(fillCloneRange);
        return original(self, flag, fillCloneRange, output);
    } else {
        //others
        return original(self, flag, range, output);
    }
}


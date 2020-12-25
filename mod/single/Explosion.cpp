//
// Created by xhy on 2020/12/23.
//
#include "lib/mod.h"
#include "lib/SymHook.h"


namespace mod {
    using namespace SymHook;
    THook(
            void,
            MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ,
            void * exp
    ) {
        original(exp);
    }
}
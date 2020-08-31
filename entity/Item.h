//
// Created by xhy on 2020/8/29.
//

#ifndef TRAPDOOR_ITEM_H
#define TRAPDOOR_ITEM_H

#include "lib/pch.h"
#include "lib/mod.h"


using namespace SymHook;

struct ItemStackBase{
    std::string getItemName();
    int getNum();
};


#endif //TRAPDOOR_ITEM_H

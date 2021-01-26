//
// Created by xhy on 2020/8/29.
//

#ifndef TRAPDOOR_ITEM_H
#define TRAPDOOR_ITEM_H


#include <string>

#include "Block.h"

namespace trapdoor {
    struct ItemStackBase {
        std::string getItemName();

        int getNum();

        void setNull();

    };
}


#endif //TRAPDOOR_ITEM_H

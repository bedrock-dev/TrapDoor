//
// Created by xhy on 2020/10/31.
//

#include "PlayerSpace.h"

bool PlayerSpace::operator<(const PlayerSpace &rhs) const {
    return self < rhs.self;
}

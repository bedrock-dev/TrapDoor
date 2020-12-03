//
// Created by xhy on 2020/10/31.
//

#include "PlayerBuffer.h"


bool PlayerBuffer::operator<(const PlayerBuffer &rhs) const {
    return this->rightPosition < rhs.rightPosition;
}

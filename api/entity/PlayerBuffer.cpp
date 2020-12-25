//
// Created by xhy on 2020/10/31.
//

#include "PlayerBuffer.h"

namespace trapdoor {
    bool RightClickCache::operator==(const RightClickCache &rhs) const {
        if (!(x == rhs.x &&
              y == rhs.y &&
              z == rhs.z))
            return false;
        auto distance2 = (dx - rhs.dx) * (dx - rhs.dx) + (dy - rhs.dy) * (dy - rhs.dy) + (dz - rhs.dz) * (dz - rhs.dz);
        return distance2 < 0.0001f;
    }

    bool RightClickCache::operator!=(const RightClickCache &rhs) const {
        return !(rhs == *this);
    }
}
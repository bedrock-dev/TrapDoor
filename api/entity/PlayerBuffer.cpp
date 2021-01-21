//
// Created by xhy on 2020/10/31.
//

#include "PlayerBuffer.h"

namespace trapdoor {
	bool RightClickCache::operator==(const RightClickCache& rhs) const {
		if (!(x == rhs.x && y == rhs.y && z == rhs.z))
			return false;
		return (gameTick - rhs.gameTick) < 4;
	}

	bool RightClickCache::operator!=(const RightClickCache& rhs) const {
		return !(rhs == *this);
	}
}  // namespace trapdoor

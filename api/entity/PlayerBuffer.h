//
// Created by xhy on 2020/10/31.
//

#ifndef TRAPDOOR_PLAYER_BUFFER_H
#define TRAPDOOR_PLAYER_BUFFER_H

#include "graphics/BlockPos.h"
#include "Actor.h"

namespace trapdoor {
	struct RightClickCache {
		uint64_t gameTick = 0;
		int x = 0;
		int y = 0;
		int z = 0;

		bool operator==(const RightClickCache& rhs) const;

		bool operator!=(const RightClickCache& rhs) const;
	};

	//这个结构专门存储玩家个人相关的缓存信息(相当于玩家的一个私人空间),后面可能加新东西
	struct PlayerBuffer {
		RightClickCache rightClickCache;  //玩家右键缓存，作为右键检测使用
	};
}  // namespace trapdoor

#endif	// TRAPDOOR_PLAYER_BUFFER_H

//
// Created by xhy on 2020/8/29.
//

#include "Item.h"
#include <string>
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "block/Block.h"
#include "PlayerBuffer.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
	using namespace SymHook;

	std::string ItemStackBase::getItemName() {
		std::string name;
		SYM_CALL(
			void (*)(ItemStackBase*, std::string*),
			MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
			this, &name);
		return name;
	}

	int ItemStackBase::getNum() { return (int)*((unsigned char*)this + 34); }

	void ItemStackBase::setNull() {
		SYM_CALL(void (*)(ItemStackBase*),
				 SymHook::MSSYM_B1QA7setNullB1AE13ItemStackBaseB2AAA7UEAAXXZ,
				 this);
	}
}  // namespace trapdoor

using namespace SymHook;
//右键代理类
THook(
	void,
	MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z,
	void* item,
	trapdoor::ItemStackBase* itemStack,
	trapdoor::Actor* player,
	int x,
	int y,
	int z,
	unsigned int facing,
	float dx,
	float dy,
	float dz) {
	uint64_t gameTick = trapdoor::bdsMod->getLevel()->getGameTick();
	// L_INFO("%.2f %.2f %.2f,tick =  %llu", x, y, z, gameTick);
	trapdoor::RightClickCache targetCache{gameTick, x, y, z};

	auto& playerCache =
		trapdoor::bdsMod->getPlayerBuffer()[player->getNameTag()]
			.rightClickCache;
	//下面用一个简单的缓存 + 判定消除重复点击
	if (playerCache != targetCache) {
		//响应右键事件
		trapdoor::BlockPos pos(x, y, z);
		const trapdoor::Vec3 vec3(dx, dy, dz);
		trapdoor::bdsMod->useOnHook(player, itemStack->getItemName(), pos,
									facing, vec3);
		playerCache = targetCache;
	}
	original(item, itemStack, player, x, y, z, facing, dx, dy, dz);
}

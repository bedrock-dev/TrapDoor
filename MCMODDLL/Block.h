#pragma once
#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include <vector>
using namespace SymHook;

std::vector<Vec3> cachePosList;
/**
 * 计算两点之间的距离 包括欧氏距离以及曼哈顿距离
 * @param p1 第一个点
 * @param p2 第二个点
 * @param useManhattan 是否采用曼哈顿距离
 * @param withY y坐标是否计算在内
 * @return 距离值
 */
double distance(Vec3 p1,Vec3 p2,bool useManhattan,bool withY) {
	auto dx = fabs(p2.x - p1.x);
	auto dy = withY ? fabs(p2.y - p1.y):0;
	auto dz = fabs(p2.z - p1.z);
	return  useManhattan? dx + dy + dz:sqrt(dx *dx + dy*dy + dz*dz);
}

/**
 * Hook 用铲子右击方块的函数
 */
THook(
	void,
	MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z,
	void* a1,
	void* a2,
	void* actor,
	int* blockPos,
	float a4,
	float a5,
	float a6
) {
	Vec3 pos(blockPos[0], blockPos[1], blockPos[2]);
	if (enableMarkPos) {
		if (cachePosList.empty()) {
			cachePosList.emplace_back(pos);
			cachePosList.emplace_back(pos);
		}
		else {
			cachePosList[0] = cachePosList[1];
			cachePosList[1] = pos;
		}
		if (cachePosList[0] != cachePosList[1]) {
			char str[256];
			sprintf_s(str, "(%d,%d,%d),(%d,%d,%d):%.2f(%.2f),%d(%d)\n",
				(int)cachePosList[0].x,
				(int)cachePosList[0].y,
				(int)cachePosList[0].z,
				(int)cachePosList[1].x,
				(int)cachePosList[1].y,
				(int)cachePosList[1].z,
				distance(cachePosList[0], cachePosList[1], false, true),
				distance(cachePosList[0], cachePosList[1], false, false),
				(int)distance(cachePosList[0], cachePosList[1], true, true),
				(int)distance(cachePosList[0], cachePosList[1], true, false)
			);
            gamePrintf(str);
		}
	}
	else {
		original(a1, a2, actor, blockPos, a4, a5, a6);
	}
}


//THook(
//	void,
//	MSSYM_B2QUA5useOnB1AE16RedStoneDustItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z,
//	void* a1,
//	void* a2,
//	void* actor,
//	int * blockPos,
//	float a4,
//	float a5,
//	float a6
//) {
//	original(a1, a2, actor, blockPos, a4, a5, a6);
//	original(a1, a2, actor, blockPos, a4, a5, a6);
//	printf("right click,pos is %d %d %d\n", blockPos[0], blockPos[1], blockPos[2]);
//	void* block = SYM_CALL(
//		void* (*)(void*, int, int, int),
//		MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z
//		,globalBlockSource,
//		blockPos[0], blockPos[1]-1, blockPos[2]
//	);
//	std::string debugStr;
//	SYM_CALL(
//		void(*)(void* block, std::string&),
//		MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
//		block,debugStr);
//	sendLocalMessage(debugStr);
//	SYM_CALL(
//		void(*)(void *,int,int,int,void *,int),
//		MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NHHHAEBVBlockB2AAA1HB1AA1Z,
//		globalBlockSource, blockPos[0], blockPos[1]+1, blockPos[2],
//		block,0
//	);
//}

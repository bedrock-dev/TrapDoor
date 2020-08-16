#pragma once

#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include <vector>

using namespace SymHook;

std::vector<Vec3> cachePosList;

/**
 * Hook 用铲子右击方块的函数
 * 老实说这里的功能蛮费的
 */
THook(
        void,
        MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z,
        void *a1,
        void *a2,
        void *actor,
        int *blockPos,
        float a4,
        float a5,
        float a6
) {
    Vec3 pos(blockPos[0], blockPos[1], blockPos[2]);
    BlockPos bp(blockPos[0], blockPos[1], blockPos[2]);
    //printf("%d %d %d\n", blockPos[0], blockPos[1], blockPos[2]);
    //   villageHelper.POIBelong(&bp);
    if (enableMarkPos) {
        if (cachePosList.empty()) {
            cachePosList.emplace_back(pos);
            cachePosList.emplace_back(pos);
        } else {
            cachePosList[0] = cachePosList[1];
            cachePosList[1] = pos;
        }
        if (cachePosList[0] != cachePosList[1]) {
            gamePrintf("(%d,%d,%d),(%d,%d,%d):%.2f(%.2f),%d(%d)\n",
                       (int) cachePosList[0].x,
                       (int) cachePosList[0].y,
                       (int) cachePosList[0].z,
                       (int) cachePosList[1].x,
                       (int) cachePosList[1].y,
                       (int) cachePosList[1].z,
                       distance(cachePosList[0], cachePosList[1], false, true),
                       distance(cachePosList[0], cachePosList[1], false, false),
                       (int) distance(cachePosList[0], cachePosList[1], true, true),
                       (int) distance(cachePosList[0], cachePosList[1], true, false)
            );
            std::string str = "minecraft:redstone_wire_dust_particle";
            spawnLineParticle(&cachePosList[0], &cachePosList[1], str);
        }
    } else {
        original(a1, a2, actor, blockPos, a4, a5, a6);
    }
}

//这里是红石粉右击事件，暂时关闭了
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

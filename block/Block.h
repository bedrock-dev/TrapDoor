#pragma once

#include "lib/mod.h"
#include "lib/SymHook.h"
#include <vector>
#include "graphics/BlockPos.h"
#include "block/BlockLegacy.h"

struct Biome;
class BlockLegacy;

/*
 * 方块接口
 */
class Block {
public:

    // 获取方块legacy
    BlockLegacy *getLegacy();

    //获取方块名称(和item返回的名称不一样，不知道Mojang怎么想的)
    std::string getName();

    //获取特殊值
    int getVariant();

    //是否是空气
    bool isAir();
};

/*
 * 方块实体接口
 */
class BlockActor {
public:
    //获取位置
    BlockPos *getPosition();
    //获取方块对象
    Block *getBlock();
};



/*
 * 红石组件接口
 */
class BaseCircuitComponent {
public:
    int getStrength();

    int getVar2();

    int getPowerCount();

    int getAcceptHalfPulse();

    int getHalfPulse();

    void setAcceptHalfPulse();

    void basePrint();

    void printRepeater();

    void printTorch(BlockPos blockPos);
};


class CircuitSceneGraph {
public:
    BaseCircuitComponent *getBaseCircuitComponent(BlockPos *pos);
};





































//这里是红石粉右击事件，暂时关闭了
//THook(
//	void,
//	MSSYM_B2QUA5useOnB1AE16RedStoneDustItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z,
//	void* a1,
//	void* a2,
//	void* hopperBlockActor,
//	int * blockPos,
//	float a4,
//	float a5,
//	float a6
//) {
//	original(a1, a2, hopperBlockActor, blockPos, a4, a5, a6);
//	original(a1, a2, hopperBlockActor, blockPos, a4, a5, a6);
//	printf("right click,pos is %d %d %d\commandMap", blockPos[0], blockPos[1], blockPos[2]);
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

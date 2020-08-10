#pragma once
#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "Shell.h"
#include "SymHook.h"
#include "Village.h"
#include <vector>
#include <chrono>
using namespace SymHook;
typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END auto elapsed = timer_clock::now() - start; long long timeReslut =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();




void extraTask() {
	if (!enableExtraTickWork)return;
	
	//here are the works;
	villageTask();
}

void worldFrozen() {
	if (tickStatus == TickStatus::Normal) {
		tickStatus = TickStatus::Frozen;
		forwardTickNum = 0;
		sendText("the world has been frozen\n");
	}
	else
	{
		sendText("this command must be run in normal status\n");
	}
}

void worldReset() {
	if (forwardTickNum > 0) {
		sendText("forwarding, try later\n");
	}
	else
	{
		tickStatus = TickStatus::Normal;
		SlowTimes = 0;
		sendText("reset tick status\n");
	}
}

void WorldSlow(int times) {
	if (tickStatus == TickStatus::Normal) {
		sendText("world has slowed\n");
		tickStatus = TickStatus::Slow;
		SlowTimes = times;
	}
	else
	{
		sendText("this command must be run at normal status\n");
	}
}

void worldForword(int tickNum) {
	if (tickStatus == TickStatus::Frozen) {
		forwardTickNum = tickNum;
		tickStatus = TickStatus::Forword;
	}
	else
	{
		sendText("this command must be run at frozen status\n");
	}

}



void worldProfile() {
	sendText("start profiling");
	profileStart = true;
	profileRound = 10;
}

void calProfile() {
	char msg[512];

	sprintf_s(msg, "mspt: %.3f ms\nredstone: %.3f ms\nlevel: %.3f ms\n    - dim(chunk (un)load,village): %.3f ms\n" \
		"    - player: %.3f ms\n        - chunk: %.3f ms\n            - random tick & env: %.3f ms\n"\
		"            - blockEntities: %.3f ms\n            - (de)spawn: %.3f ms",
		(double)redstoenUpdateTime / 9000 + (double)levelTickTime / 10000,
		(double)redstoenUpdateTime / 9000,
		(double)levelTickTime / 10000,
		(double)dimTickTime /10000,
		(double)playerTickTime /10000,
		(double)chunkTickTime /10000,
		(double)randTickTime/10000,
		(double)blockEntityTickTime/10000,
		(double)SpawnerTickTime/10000
		);
	redstoenUpdateTime = 0;
	levelTickTime = 0;
	dimTickTime = 0;
	playerTickTime = 0;
	chunkTickTime = 0;
	randTickTime = 0;
	pendingTickTime = 0;
	blockEntityTickTime = 0;
	SpawnerTickTime = 0;
	sendText(msg);
}

//世界运行 Level::tick
THook(void,
	MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ,
	void* l) {
	if (!level) { level = l; }
	if (tickStatus == TickStatus::Normal) {

		if (profileStart) {
			
			TIMER_START
			original(l);
			extraTask();
			TIMER_END
			levelTickTime += timeReslut;
			profileRound--;
			if (profileRound == 0) {
				profileStart = false;
				calProfile();
			}
		}
		else {
			original(l);
			extraTask();
		}
	}

	else if (tickStatus == TickStatus::Forword)
	{
		sendText("forward start ,please wait\n");
		for (int i = 0; i < forwardTickNum; i++) {
			original(l);
			SYM_CALL(
				void(*)(void*),
				MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ,
				dimension
			);
		}
		sendText("end forward\n");
		forwardTickNum = 0;
		tickStatus = TickStatus::Frozen;
	}
	else if (tickStatus == TickStatus::Slow)
	{
		if (slowCounter % SlowTimes == 0) {
			original(l);
		}
		slowCounter = (slowCounter + 1) % SlowTimes;
	}
}






//玩家更新世界 ServerPlayer::tickWorld
THook(
	void,
	MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z,
	void* p,
	void* tick
) {
	if (!player)player = p;
	//如果是一般状态
	if (profileStart) {
		TIMER_START
		original(p, tick);
		TIMER_END
			playerTickTime += timeReslut;
	}
	else {
		original(p, tick);
	}
}




//维度更新 Dimension::tick
THook(
	void,
	MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ,
	void* dim
) {
	if (!dimension)dimension = dim;
	if (profileStart) {
		TIMER_START
			original(dim);
		TIMER_END
			dimTickTime += timeReslut;
	}
	else
	{
		original(dim);
	}
	
}

//区块更新 LevelChunk::tick
THook(
	void,
	MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z,
	void* levelChunk,
	void* blockSource,
	void* tick
) {
	if (!globalBlockSource)globalBlockSource = blockSource;
	if (profileStart) {
	TIMER_START
	original(levelChunk, blockSource, tick);
	TIMER_END
	chunkTickTime += timeReslut;
	}else{
		original(levelChunk, blockSource, tick);
	}
}

//天气和随机刻 LevelChunk::tickBlocks
THook(
	void,
	MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z,
	void* levelChunk,
	void* blockSource,
	INT64 a3,
	int a4
) {

	if (profileStart) {
		TIMER_START
			original(levelChunk, blockSource, a3, a4);
		TIMER_END
		randTickTime += timeReslut;
	}
	else {
		original(levelChunk, blockSource, a3, a4);
	}

}


//方块实体 LevelChunk::tickEntities
THook(
	void,
	MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z,
	void* levelChunk,
	void* blockSource
) {

	if (profileStart) {
		TIMER_START
			original(levelChunk, blockSource);
		TIMER_END
			blockEntityTickTime += timeReslut;
	}
	else {
		original(levelChunk, blockSource);
	}
	
}


//mobspawn Spawner::tick
THook(
	void,
	MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEBVLevelChunkB3AAAA1Z,
	void* swr,
	void* blockSource,
	void* chunk
) {
	if (!spawner)spawner = swr;

	if (profileStart) {
		TIMER_START
			original(swr, blockSource, chunk);
		TIMER_END
			SpawnerTickTime += timeReslut;
	}
	else {
		original(swr, blockSource, chunk);
	}
	
}

//计划刻更新  BlockTickingQueue::pendingTicks
THook(
	void,
	MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z,
	void* queue,
	void* source,
	int flag,
	bool a1
) {
	original(queue, source, flag, a1);
	
}

//红石更新
THook(
	void,
	MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ,
	void* dim
) {
	if (tickStatus == TickStatus::Normal){
		if (profileStart) {
			TIMER_START
			original(dim);
			TIMER_END
			redstoenUpdateTime += timeReslut;
		}
		else {
			original(dim);
		}
	}

	if (tickStatus == TickStatus::Forword) {
		original(dim);
	}
	else if (tickStatus == TickStatus::Slow)
	{
		if (slowCounter % SlowTimes == 0) {
			original(dim);
		}
	}
}

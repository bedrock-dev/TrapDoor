#pragma once
#pragma once
#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "Shell.h"
#include <random>
using namespace SymHook;

bool isSlimeChunk(INT32 x,INT32 z) {
	auto seed =  (x * 0x1f1f1f1f) ^ z;
	std::mt19937 mt(seed);
	return mt() % 10 == 0;
}

int getMobCount(void *spawner) {
	if (!spawner)return -1;
	return *((UINT32*)spawner + 48);
}

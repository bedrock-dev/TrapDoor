#pragma once

//这里存了所有的全局变量和全局函数


#include "mod.h"
#include <string>
using namespace SymHook;

void* player = nullptr; //全局玩家对象
void* level = nullptr; //全局存档对象
void* dimension = nullptr; //全局维度对象
void* globalBlockSource = nullptr;

enum class TickStatus {
	Frozen,
	Normal,
	Slow,
	Forword
};



TickStatus tickStatus = TickStatus::Normal;
//tick运行控制
int  SlowTimes = 1;  //放慢倍数
int slowCounter = 0; //计数器
int forwardTickNum = 0; //快进的tick数量


//性能分析
bool profileStart = false;
int profileRound = 0;
long long redstoenUpdateTime = 0;
long long playerTickTime = 0;
long long levelTickTime = 0;
	long long dimTickTime = 0;
	long long chunkTickTime = 0;
		long long randTickTime = 0;
		long long pendingTickTime = 0;
		long long blockEntityTickTime = 0;
		long long SpawnerTickTime = 0;



void msg(std::string& s) {
	if (!player)return;
	std::vector<std::string> v;
	SYM_CALL(
		void(*)(void*, std::string&, std::vector<std::string>&),
		MSSYM_MD5_39e2c315b1969108fef04029f8bddbb8,
		player, s, v);

}
void sendText(const char* m) {
	std::string s(m);
	msg(s);
}


struct Vec3 {
	float x;
	float y;
	float z;
};

struct AABB
{
	Vec3 p1;
	Vec3 p2;
	AABB(Vec3 _p1, Vec3 _p2) {
		p1.x = _p1.x;
		p1.y = _p1.y;
		p1.z = _p1.z;
		p2.x = _p2.x;
		p2.y = _p2.y;
		p2.z = _p2.z;
	}
};

void spawnParticle(float* p , std::string &type) {
	//printf("spawn particle at %f %f %f\n",p[0],p[1],p[2]);
	SYM_CALL(
		void(*)(void*, std::string, float*, void*),
		MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb,
		level, type, p, dimension
	);
}

void spawnRectangleParticle(AABB aabb, std::string &type) {
	for (auto i = aabb.p1.x + 0.5; i<= aabb.p2.x+0.5 ; i+=0.5)
	{
		float point[3] = {i,aabb.p1.y + 0.5,aabb.p1.z + 0.5 };
		spawnParticle(point, type); //p1y p1z
		point[1] = aabb.p2.y + 0.5; //p2y 1z
		spawnParticle(point, type);
		point[2] = aabb.p2.z + 0.5; //p2y p2z
		spawnParticle(point,type);
		point[1] = aabb.p1.y + 0.5; //p1y p2z
		spawnParticle(point, type);
	}

	for (auto i = aabb.p1.y + 0.5; i <= aabb.p2.y + 0.5; i+=0.5)
	{
		float point[3] = {aabb.p1.x + 0.5,i,aabb.p1.z + 0.5 };
		spawnParticle(point, type); //p1x p1z
		point[0] = aabb.p2.x + 0.5; //p2x p1z
		spawnParticle(point, type);
		point[2] = aabb.p2.z + 0.5; //p2x p2z
		spawnParticle(point, type);
		point[0] = aabb.p1.x + 0.5; //p1x p2z
		spawnParticle(point, type);
	}

	for (auto i = aabb.p1.z + 0.5; i <= aabb.p2.z+0.5; i+=0.5)
	{
		float point[3] = { aabb.p1.x + 0.5,aabb.p1.y + 0.5,i };
		spawnParticle(point, type); //p1x p1z
		point[0] = aabb.p2.x + 0.5; //p2x p1z
		spawnParticle(point, type);
		point[1] = aabb.p2.y + 0.5; //p2x p2z
		spawnParticle(point, type);
		point[0] = aabb.p1.x + 0.5; //p1x p2z
		spawnParticle(point, type);
	}
}


bool enableVillageShow = false;
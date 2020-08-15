#pragma once

//这里存了所有的全局变量和全局函数
#include <vector>
#include "SymHook.h"
#include "detours.h"
#include "mod.h"
#include <string>

using namespace SymHook;

void *player = nullptr; //全局玩家对象
void *level = nullptr; //全局存档对象
void *dimension = nullptr; //全局维度对象
void *globalBlockSource = nullptr;
void *spawner = nullptr;
enum class TickStatus {
    Frozen,
    Normal,
    Slow,
    Forward
};


TickStatus tickStatus = TickStatus::Normal;
//tick运行控制
int SlowTimes = 1;  //放慢倍数
int slowCounter = 0; //计数器
int forwardTickNum = 0; //快进的tick数量


//性能分析
bool profileStart = false;
int profileRound = 0;
long long redstoneUpdateTime = 0;
long long playerTickTime = 0;
long long levelTickTime = 0;
long long dimTickTime = 0;
long long chunkTickTime = 0;
long long randTickTime = 0;
long long blockEntityTickTime = 0;
long long spawnerTickTime = 0;


void sendLocalMessage(std::string &s) {
    if (!player)return;
    std::vector<std::string> v;
    v.emplace_back("test");
    SYM_CALL(
            void(*)(bool, void *, std::string &, std::vector<std::string> &),
            MSSYM_MD5_24be62e9330073695808606844de0d99,
            true, player, s, v);
}

//void gamePrintf(const char *m) {
//    std::string s(m);
//    sendLocalMessage(s);
//}

//this code is from https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template<typename ... Args>
void gamePrintf(const std::string &format, Args ... args) {
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size <= 0) { throw std::runtime_error("Error during formatting."); }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    auto str = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    sendLocalMessage(str);
}


struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() = default;

    Vec3(int _x, int _y, int _z) : x((float) _x), y((float) _y), z((float) _z) {}

    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    bool operator==(const Vec3 &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const Vec3 &v) const {
        return x != v.x || y != v.y || z != v.z;
    }


};

struct AABB {
    Vec3 p1{};
    Vec3 p2{};

    AABB(Vec3 _p1, Vec3 _p2) {
        p1.x = _p1.x;
        p1.y = _p1.y;
        p1.z = _p1.z;
        p2.x = _p2.x;
        p2.y = _p2.y;
        p2.z = _p2.z;
    }
};

void spawnParticle(float *p, std::string &type) {
    for (int i = 0; i < 3; ++i)
        p[i] += 0.5;
    SYM_CALL(
            void(*)(void * , std::string, float *, void *),
            MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb,
            level, type, p, dimension
    );
}

void spawnRectangleParticle(AABB aabb, std::string &type) {


    for (auto i = static_cast<int>(aabb.p1.x); i <= aabb.p2.x; i++) {
        float point[3] = {(float) i, aabb.p1.y, aabb.p1.z};
        spawnParticle(point, type); //p1y p1z
        point[1] = aabb.p2.y; //p2y 1z
        spawnParticle(point, type);
        point[2] = aabb.p2.z; //p2y p2z
        spawnParticle(point, type);
        point[1] = aabb.p1.y; //p1y p2z
        spawnParticle(point, type);
    }
    for (auto i = static_cast<int>(aabb.p1.y); i <= aabb.p2.y; i++) {
        float point[3] = {aabb.p1.x, static_cast<float>(i), aabb.p1.z};
        spawnParticle(point, type); //p1x p1z
        point[0] = aabb.p2.x; //p2x p1z
        spawnParticle(point, type);
        point[2] = aabb.p2.z; //p2x p2z
        spawnParticle(point, type);
        point[0] = aabb.p1.x; //p1x p2z
        spawnParticle(point, type);
    }

    for (auto i = static_cast<int>(aabb.p1.z); i <= aabb.p2.z; i++) {
        float point[3] = {aabb.p1.x, aabb.p1.y, static_cast<float>(i)};
        spawnParticle(point, type); //p1x p1z
        point[0] = aabb.p2.x; //p2x p1z
        spawnParticle(point, type);
        point[1] = aabb.p2.y; //p2x p2z
        spawnParticle(point, type);
        point[0] = aabb.p1.x; //p1x p2z
        spawnParticle(point, type);
    }
}


bool enableMarkPos = false;
bool enableVillageShow = false;
bool enableExtraTickWork = true;
bool enableExplosion = true;

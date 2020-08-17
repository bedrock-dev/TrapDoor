#pragma once

#include <vector>
#include "SymHook.h"
#include "detours.h"
#include "mod.h"
#include <string>
#include <ostream>

using namespace SymHook;

void *player = nullptr; //全局玩家对象
void *level = nullptr; //全局存档对象
void *dimension = nullptr; //全局维度对象
void *globalBlockSource = nullptr; //全局bs对象
void *spawner = nullptr; //全局刷怪器对象
void *villageManager = nullptr; //全局村庄管理器对象
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

void error(const std::string &s) {
    gamePrintf("§c%s", s.c_str());
}

void warning(const std::string &s) {
    gamePrintf("§6%s", s.c_str());
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

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3) {
        os << "[" << vec3.x << "," << vec3.y << "," << vec3.z << "]";
        return os;
    }
};

/**
 * 计算两点之间的距离 包括欧氏距离以及曼哈顿距离
 * @param p1 第一个点
 * @param p2 第二个点
 * @param useManhattan 是否采用曼哈顿距离
 * @param withY y坐标是否计算在内
 * @return 距离值
 */
double distance(Vec3 p1, Vec3 p2, bool useManhattan, bool withY) {
    auto dx = fabs(p2.x - p1.x);
    auto dy = withY ? fabs(p2.y - p1.y) : 0;
    auto dz = fabs(p2.z - p1.z);
    return useManhattan ? dx + dy + dz : sqrt(dx * dx + dy * dy + dz * dz);
}

struct BlockPos {
    int x;
    int y;
    int z;

    BlockPos() = default;

    BlockPos(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

    BlockPos(float _x, float _y, float _z) : x((int) _x), y((int) _y), z((int) _z) {}

    bool operator==(const BlockPos &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const BlockPos &v) const {
        return x != v.x || y != v.y || z != v.z;
    }

    friend std::ostream &operator<<(std::ostream &os, const BlockPos &vec3) {
        os << "[" << vec3.x << "," << vec3.y << "," << vec3.z << "]";
        return os;
    }

    Vec3 toVec3() const {
        return {x, y, z};
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
    for (auto i = 0; i < 3; ++i)
        p[i] += 0.5;
    SYM_CALL(
            void(*)(void * , std::string, float *, void *),
            MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb,
            level, type, p, dimension
    );
}

//等距切分坐标
std::vector<float> cut(float begin, float end, int num) {
    float distance = (end - begin) / (float) num;
    std::vector<float> result;
    result.reserve(num);
    for (int i = 0; i <= num; ++i)
        result.emplace_back(begin + (float) i * distance);
    return result;
}


void spawnLineParticle(Vec3 *p1, Vec3 *p2, std::string &type) {
    float num = sqrt((p1->x - p2->x) * (p1->x - p2->x) +
                     (p1->y - p2->y) * (p1->y - p2->y) +
                     (p1->z - p2->z) * (p1->z - p2->z));
    for (int i = 0; i <= num; i++) {
        float point[3] = {p1->x + (p2->x - p1->x) / num * (float) i,
                          p1->y + (p2->y - p1->y) / num * (float) i,
                          p1->z + (p2->z - p1->z) / num * (float) i,
        };
        spawnParticle(point, type);
    }
}

void spawnRectangleParticle(AABB aabb, std::string &type) {

    auto pointList = cut(aabb.p1.x, aabb.p2.x, (int) (aabb.p2.x - aabb.p1.x) / 3);
    for (auto i :pointList) {
        float point[3] = {i, aabb.p1.y, aabb.p1.z};
        spawnParticle(point, type); //p1y p1z
        point[1] = aabb.p2.y; //p2y 1z
        spawnParticle(point, type);
        point[2] = aabb.p2.z; //p2y p2z
        spawnParticle(point, type);
        point[1] = aabb.p1.y; //p1y p2z
        spawnParticle(point, type);
    }
    pointList = cut(aabb.p1.y, aabb.p2.y, (int) (aabb.p2.y - aabb.p1.y) / 3);
    for (auto i: pointList) {
        float point[3] = {aabb.p1.x, static_cast<float>(i), aabb.p1.z};
        spawnParticle(point, type); //p1x p1z
        point[0] = aabb.p2.x; //p2x p1z
        spawnParticle(point, type);
        point[2] = aabb.p2.z; //p2x p2z
        spawnParticle(point, type);
        point[0] = aabb.p1.x; //p1x p2z
        spawnParticle(point, type);
    }

    pointList = cut(aabb.p1.z, aabb.p2.z, (int) (aabb.p2.z - aabb.p1.z) / 3);
    for (auto i:pointList) {
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

bool mobSpawnCounterStart = false;
int mobTickCounter = 0;
//
// Created by xhy on 2020/8/25.
//
#include "Particle.h"
#include "common/Trapdoor.h"
#include "lib/mod.h"
#include <string>

using namespace SymHook;

#include "entity/Actor.h"
#include "level/Level.h"

namespace particle {
//    const ParticleType BALLOON_GAS = "minecraft:balloon_gas_particle";
    //  const ParticleType HEART = "minecraft:heart_particle  ";
}

void spawnParticle(Vec3 p, std::string &type) {
    auto pos = p.toBlockPos();
    auto player = globalLevel->getNearestPlayer(pos);
    if (!player)return;
    if (math::distance(p, *player->getPos()) > particleViewDistance)return;
    p.x += 0.5;
    p.y += 0.5;
    p.z += 0.5;
    SYM_CALL(
            void(*)(Level * , std::string, Vec3 *, void *),
            MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb,
            globalLevel, type, &p, player->getDimension()
    );
}


void spawnRectangleParticle(AABB aabb, std::string &type) {
    auto pointList = math::cut(aabb.p1.x, aabb.p2.x, (int) (aabb.p2.x - aabb.p1.x) / 3);
    for (auto i :pointList) {
        Vec3 point = {i, aabb.p1.y, aabb.p1.z};
        spawnParticle(point, type); //p1y p1z
        point.y = aabb.p2.y; //p2y 1z
        spawnParticle(point, type);
        point.z = aabb.p2.z; //p2y p2z
        spawnParticle(point, type);
        point.y = aabb.p1.y; //p1y p2z
        spawnParticle(point, type);
    }
    pointList = math::cut(aabb.p1.y, aabb.p2.y, (int) (aabb.p2.y - aabb.p1.y) / 3);
    for (auto i: pointList) {
        Vec3 point = {aabb.p1.x, static_cast<float>(i), aabb.p1.z};
        spawnParticle(point, type); //p1x p1z
        point.x = aabb.p2.x; //p2x p1z
        spawnParticle(point, type);
        point.z = aabb.p2.z; //p2x p2z
        spawnParticle(point, type);
        point.x = aabb.p1.x; //p1x p2z
        spawnParticle(point, type);
    }

    pointList = math::cut(aabb.p1.z, aabb.p2.z, (int) (aabb.p2.z - aabb.p1.z) / 3);
    for (auto i:pointList) {
        Vec3 point = {aabb.p1.x, aabb.p1.y, static_cast<float>(i)};
        spawnParticle(point, type); //p1x p1z
        point.x = aabb.p2.x; //p2x p1z
        spawnParticle(point, type);
        point.y = aabb.p2.y; //p2x p2z
        spawnParticle(point, type);
        point.x = aabb.p1.x; //p1x p2z
        spawnParticle(point, type);
    }
}
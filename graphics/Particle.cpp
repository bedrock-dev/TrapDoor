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
#include "Graphics.h"

namespace particle {
//    const ParticleType BALLOON_GAS = "minecraft:balloon_gas_particle";
    //  const ParticleType HEART = "minecraft:heart_particle  ";
}

void spawnParticle(Vec3 p, std::string &type) {
    auto pos = p.toBlockPos();
    auto player = globalLevel->getNearestPlayer(pos);
    if (!player) {
        return;
    }
    //   if (math::distance(p, *player->getPos()) > particleViewDistance)return;
//    p.x += 0.5;
//    p.y += 0.5;
//    p.z += 0.5;
    SYM_CALL(
            void(*)(Level * , std::string, Vec3 *, void *),
            MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb,
            globalLevel, type, &p, player->getDimension()
    );
}


void spawnRectangleParticle(const AABB  &aabb) {
    auto p1 = aabb.p1, p2 = aabb.p2;
    auto dx = p2.x - p1.x;
    auto dy = p2.y - p1.y;
    auto dz = p2.z - p1.z;
    graphics::drawLine(p1, FACING::POS_X, dx, graphics::COLOR::RED);
    graphics::drawLine(p1, FACING::POS_Y, dy, graphics::COLOR::GREEN);
    graphics::drawLine(p1, FACING::POS_Z, dz, graphics::COLOR::BLUE);

    Vec3 p3{p2.x, p1.y, p2.z};
    graphics::drawLine(p3, FACING::NEG_X, dx, graphics::COLOR::WHITE);
    graphics::drawLine(p3, FACING::POS_Y, dy, graphics::COLOR::WHITE);
    graphics::drawLine(p3, FACING::NEG_Z, dz, graphics::COLOR::WHITE);
    Vec3 p4{p2.x, p2.y, p1.z};
    graphics::drawLine(p4, FACING::NEG_X, dx, graphics::COLOR::WHITE);
    graphics::drawLine(p4, FACING::NEG_Y, dy, graphics::COLOR::WHITE);
    graphics::drawLine(p4, FACING::POS_Z, dz, graphics::COLOR::WHITE);

    Vec3 p5{p1.x, p2.y, p2.z};
    graphics::drawLine(p5, FACING::POS_X, dx, graphics::COLOR::WHITE);
    graphics::drawLine(p5, FACING::NEG_Y, dy, graphics::COLOR::WHITE);
    graphics::drawLine(p5, FACING::NEG_Z, dz, graphics::COLOR::WHITE);
}
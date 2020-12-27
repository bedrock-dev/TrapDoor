//
// Created by xhy on 2020/8/25.
//
#include "Particle.h"
#include <string>
#include "lib/mod.h"
#include "lib/SymHook.h"

#include "Graphics.h"
#include "entity/Actor.h"
#include "world/Level.h"
#include "BDSMod.h"
#include "tools/DirtyLogger.h"

//todo
namespace trapdoor {
    using namespace SymHook;

    void spawnParticle(Vec3 p, std::string &type) {
        auto pos = p.toBlockPos();
        auto level = trapdoor::bdsMod->getLevel();
        if (!level) {
            L_ERROR("level is null");
            return;
        }
        auto player = level->getNearestPlayer(pos);
        if (!player) {
            return;
        }
        //  if (p.distanceTo(*player->getPos()) > static_cast<float>(particleViewDistance))return;
        SYM_CALL(void(*)(Level * , std::string, Vec3 *, void *),
                 MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb, level, type, &p,
                 player->getDimension());
    }


    void spawnRectangleParticle(const AABB &aabb) {
        auto p1 = aabb.p1, p2 = aabb.p2;
        auto dx = p2.x - p1.x;
        auto dy = p2.y - p1.y;
        auto dz = p2.z - p1.z;
        drawLine(p1, FACING::POS_X, dx, COLOR::RED);
        drawLine(p1, FACING::POS_Y, dy, COLOR::GREEN);
        drawLine(p1, FACING::POS_Z, dz, COLOR::BLUE);
        Vec3 p3{p2.x, p1.y, p2.z};
        drawLine(p3, FACING::NEG_X, dx, COLOR::WHITE);
        drawLine(p3, FACING::POS_Y, dy, COLOR::WHITE);
        drawLine(p3, FACING::NEG_Z, dz, COLOR::WHITE);
        Vec3 p4{p2.x, p2.y, p1.z};
        drawLine(p4, FACING::NEG_X, dx, COLOR::WHITE);
        drawLine(p4, FACING::NEG_Y, dy, COLOR::WHITE);
        drawLine(p4, FACING::POS_Z, dz, COLOR::WHITE);

        Vec3 p5{p1.x, p2.y, p2.z};
        drawLine(p5, FACING::POS_X, dx, COLOR::WHITE);
        drawLine(p5, FACING::NEG_Y, dy, COLOR::WHITE);
        drawLine(p5, FACING::NEG_Z, dz, COLOR::WHITE);
    }

    void spawnRectangleParticleColor(const AABB &aabb, COLOR color) {
        auto p1 = aabb.p1, p2 = aabb.p2;
        auto dx = p2.x - p1.x;
        auto dy = p2.y - p1.y;
        auto dz = p2.z - p1.z;
        drawLine(p1, FACING::POS_X, dx, color);
        drawLine(p1, FACING::POS_Y, dy, color);
        drawLine(p1, FACING::POS_Z, dz, color);

        Vec3 p3{p2.x, p1.y, p2.z};
        drawLine(p3, FACING::NEG_X, dx, color);
        drawLine(p3, FACING::POS_Y, dy, color);
        drawLine(p3, FACING::NEG_Z, dz, color);
        Vec3 p4{p2.x, p2.y, p1.z};
        drawLine(p4, FACING::NEG_X, dx, color);
        drawLine(p4, FACING::NEG_Y, dy, color);
        drawLine(p4, FACING::POS_Z, dz, color);

        Vec3 p5{p1.x, p2.y, p2.z};
        drawLine(p5, FACING::POS_X, dx, color);
        drawLine(p5, FACING::NEG_Y, dy, color);
        drawLine(p5, FACING::NEG_Z, dz, color);
    }
}
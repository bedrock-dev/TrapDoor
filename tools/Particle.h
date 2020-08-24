//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_PARTICLE_H
#define TRAPDOOR_PARTICLE_H

#include "common/Common.h"
#include "common/Vec3.h"
#include <string>
#include "MathTool.h"
#include "entity/Actor.h"
#include "tools/Message.h"

void spawnParticle(Vec3 p, std::string &type) {
    if (math::distance(p, *spawn::getPos(globalPlayer)) > particleViewDistance)return;
    p.x += 0.5;
    p.y += 0.5;
    p.z += 0.5;
    if ((!globalLevel || !globalDimension))return;
    SYM_CALL(
            void(*)(void * , std::string, Vec3 *, void *),
            MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb,
            globalLevel, type, &p, globalDimension
    );
}

void spawnRectangleParticle(AABB aabb, std::string &type) {
    auto pointList = math::cut(aabb.p1.x, aabb.p2.x, (int) (aabb.p2.x - aabb.p1.x) / 4);
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
    pointList = math::cut(aabb.p1.y, aabb.p2.y, (int) (aabb.p2.y - aabb.p1.y) / 4);
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

    pointList = math::cut(aabb.p1.z, aabb.p2.z, (int) (aabb.p2.z - aabb.p1.z) / 4);
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

//void spawnLineParticle(Vec3 *p1, Vec3 *p2, std::string &type) {
//    float num = sqrt((p1->x - p2->x) * (p1->x - p2->x) +
//                     (p1->y - p2->y) * (p1->y - p2->y) +
//                     (p1->z - p2->z) * (p1->z - p2->z));
//    for (int i = 0; i <= num; i++) {
//        float point[3] = {p1->x + (p2->x - p1->x) / num * (float) i,
//                          p1->y + (p2->y - p1->y) / num * (float) i,
//                          p1->z + (p2->z - p1->z) / num * (float) i,
//        };
//        spawnParticle(point, type);
//    }
//}

#endif //TRAPDOOR_PARTICLE_H

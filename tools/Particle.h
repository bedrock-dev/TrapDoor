//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_PARTICLE_H
#define TRAPDOOR_PARTICLE_H

#include <string>
#include "MathTool.h"
#include "../lib/pch.h"


void spawnParticle(Vec3 p, std::string &type);

void spawnRectangleParticle(AABB aabb, std::string &type);

#endif //TRAPDOOR_PARTICLE_H

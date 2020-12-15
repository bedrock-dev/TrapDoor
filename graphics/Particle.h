//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_PARTICLE_H
#define TRAPDOOR_PARTICLE_H

#include <string>

#include "Graphics.h"
#include "lib/pch.h"

void spawnParticle(Vec3 p, std::string& type);

void spawnRectangleParticle(const AABB& aabb);
void spawnRectangleParticleColor(const AABB& aabb, graphics::COLOR color);
#endif	// TRAPDOOR_PARTICLE_H

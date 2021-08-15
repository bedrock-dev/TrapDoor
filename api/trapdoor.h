//
// Created by xhy on 2021/2/2.
//

#ifndef MOD_TRAPDOOR_H
#define MOD_TRAPDOOR_H

#include "Actor.h"
#include "CommandManager.h"
#include "block/Block.h"
#include "block/BlockLegacy.h"
#include "block/BlockSource.h"
#include "block/VanillaBlockType.h"
#include "graphics/AABB.h"
#include "graphics/BlockPos.h"
#include "graphics/Particle.h"
#include "graphics/Vec3.h"
#include "tools/CastHelper.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"

#define FUNC_DISABLED(p) \
    trapdoor::warning(p, "this function is blocked by developer");

#endif  // MOD_TRAPDOOR_H

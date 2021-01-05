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

    void spawnParticle(Vec3 p, std::string &type, int dimType) {
        auto pos = p.toBlockPos();
        auto level = trapdoor::bdsMod->getLevel();
        if (!level) {
            L_ERROR("level is null");
            return;
        }
        auto player = level->getNearestDimensionPlayer(pos, dimType);
        if (!player) {
            return;
        }
        //  L_DEBUG("spawn particle@ %.2f %.2f %.2f", p.x, p.y, p.z);
        auto maxDist = trapdoor::bdsMod->getCfg().particleViewDistance;
        if (p.distanceTo(*player->getPos()) > static_cast<float>(maxDist))return;
        SYM_CALL(void(*)(Level * , std::string, Vec3 *, void *),
                 MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb, level, type, &p,
                 player->getDimension());
    }


    void spawnRectangleParticle(const AABB &aabb, GRAPHIC_COLOR color, int dimType) {
        auto p1 = aabb.p1, p2 = aabb.p2;
        auto dx = p2.x - p1.x;
        auto dy = p2.y - p1.y;
        auto dz = p2.z - p1.z;
        drawLine(p1, FACING::POS_X, dx, color, dimType);
        drawLine(p1, FACING::POS_Y, dy, color, dimType);
        drawLine(p1, FACING::POS_Z, dz, color, dimType);
        Vec3 p3{p2.x, p1.y, p2.z};
        drawLine(p3, FACING::NEG_X, dx, color, dimType);
        drawLine(p3, FACING::POS_Y, dy, color, dimType);
        drawLine(p3, FACING::NEG_Z, dz, color, dimType);
        Vec3 p4{p2.x, p2.y, p1.z};
        drawLine(p4, FACING::NEG_X, dx, color, dimType);
        drawLine(p4, FACING::NEG_Y, dy, color, dimType);
        drawLine(p4, FACING::POS_Z, dz, color, dimType);

        Vec3 p5{p1.x, p2.y, p2.z};
        drawLine(p5, FACING::POS_X, dx, color, dimType);
        drawLine(p5, FACING::NEG_Y, dy, color, dimType);
        drawLine(p5, FACING::NEG_Z, dz, color, dimType);
    }

    void spawnLineParticle(const Vec3 &p, FACING facing, float length, GRAPHIC_COLOR color, int dimType) {
        drawLine(p, facing, length, color, dimType);
    }


    void spawnChunkSurfaceParticle(const ChunkPos &p, int dimID) {
        //chunkp/m chunkslimep/m
        bool isSlime = p.isSlimeChunk();
        std::string pName2 = isSlime ? "trapdoor:chunkslimep" : "trapdoor:chunkp";
        std::string pName1 = isSlime ? "trapdoor:chunkslimem" : "trapdoor:chunkm";
        ChunkPos pos{p.x * 16, p.z * 16};
        Vec3 p1{pos.x, 128, pos.z + 8};
        Vec3 p2{pos.x + 16, 128, pos.z + 8};
        Vec3 p3{pos.x + 8, 128, pos.z};
        Vec3 p4{pos.x + 8, 128, pos.z + 16};
        spawnParticle(p1, pName1, dimID);
        spawnParticle(p2, pName1, dimID);
        spawnParticle(p3, pName2, dimID);
        spawnParticle(p4, pName2, dimID);
    }
}
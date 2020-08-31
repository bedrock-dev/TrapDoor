//
// Created by xhy on 2020/8/25.
//
#include "Village.h"
#include "common/Common.h"
#include "tools/Message.h"
#include "tools/Particle.h"
#include "tools/MessageBuilder.h "

using namespace SymHook;
//village tick

namespace village {
    const size_t BOUND_OFFSET = 104;
    const size_t POPULATION_OFFSET = 22;
    const size_t GOLEM_NUM_OFFSET = 30;
    VillageHelper villageHelper; //NOLINT

    //get village population
    int Village::getPopulation() {
        return (int) *((int64_t *) this + POPULATION_OFFSET);
    }

    //get village owned iron golem num
    int Village::getIronGolemNum() {
        return (int) *((int64_t *) this + GOLEM_NUM_OFFSET);
    }

    //get village owned bed poi count(max is villager num + 32)
    int Village::getBedPOICount() {
        return
                SYM_CALL(
                        int(*)(Village * ),
                        MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ,
                        this
                );
    }

    //get worked villager num
    int Village::getWorkedVillagerNum() {
        auto timeOfDay = *(reinterpret_cast<int64_t *>(this) + 60) - 24000;
        auto begin = *(reinterpret_cast<int64_t *>(this) + 85);
        auto end = *(reinterpret_cast<int64_t *>(this) + 86);
        int num;
        for (num = 0; begin != end; begin += 16) {
            if (*(int64_t *) (begin + 8) > timeOfDay)
                ++num;
        }
        return num;
    }

    //check can spawn iron golem
    bool Village::canSpawnIronGolem() {
        auto population = getPopulation();
        auto workedNum = getWorkedVillagerNum();
        auto golemNum = getIronGolemNum();
        auto bedNum = getBedPOICount();
        int max = 20 > population ? 20 : population;
        return (float) workedNum > population * 0.75 && golemNum < population / 10 && bedNum > max;
    }

    //get village center
    BlockPos Village::getCenter() {
        BlockPos center = {
                (*((float *) this + BOUND_OFFSET + 3) + *((float *) this + BOUND_OFFSET)) / 2,
                (*((float *) this + BOUND_OFFSET + 4) + *((float *) this + BOUND_OFFSET + 1)) / 2,
                (*((float *) this + BOUND_OFFSET + 5) + *((float *) this + BOUND_OFFSET + 2)) / 2,
        };
        return center;
    }

    //get village bounds
    AABB Village::getBounds() {
        Vec3 p1 = {*((float *) this + BOUND_OFFSET + 3),
                   *((float *) this + BOUND_OFFSET + 4),
                   *((float *) this + BOUND_OFFSET + 5)};
        Vec3 p2 = {*((float *) this + BOUND_OFFSET),
                   *((float *) this + BOUND_OFFSET + 1),
                   *((float *) this + BOUND_OFFSET + 2)};
        AABB aabb(p2, p1);
        return aabb;
    }

    //get village radius
    float Village::getRadius() {
        return SYM_CALL(
                float(*)(Village * ),
                MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ,
                this
        );
    }

    int villageInterval = 0;

    void villageTask() {
        if (villageInterval % 15 == 0 && enableVillageShow) {
            villageHelper.draw();
        }
        if (villageInterval % 100 == 0) {
            villageHelper.clear();
        }
        villageInterval = (villageInterval + 1) % 300;
    }

    void listVillages() {
        villageHelper.list();
    }

    void VillageHelper::clear() {
        villageList.clear();
    }

    void VillageHelper::insert(Village *village) {
        villageList.insert(village);
    }

    void VillageHelper::draw() {
        if (enableVillageShow) {
            std::string borderParticleType = "minecraft:dragon_breath_trail";
            std::string centerParticleType = "minecraft:heart_particle";
            for (auto village:villageList) {
                if (village) {
                    spawnRectangleParticle(village->getBounds(), borderParticleType);
                    spawnParticle(village->getCenter().toVec3(), centerParticleType);
                }
            }
        }
    }

    void VillageHelper::list() {
        MessageBuilder builder;
        builder.text("here are all the ticking villages:\n");
        int i = 0;
        for (auto village : villageList) {
            if (village) {
                i++;
                auto aabb = village->getBounds();
                builder.num(i).text(": ")
                        .pos(village->getCenter())
                        .text("r")
                        .num(village->getRadius())
                        .text(" p")
                        .num(village->getWorkedVillagerNum())
                        .text("/")
                        .num(village->getPopulation())
                        .text(" g:")
                        .num(village->getIronGolemNum())
                        .text(" b:")
                        .num(village->getBedPOICount())
                        .text(" s:")
                        .num((int)village->canSpawnIronGolem())
                        .text(" ")
                        .aabb(aabb)
                        .text("\n");
            }
        }
        builder.send();
    }
}


THook(
        void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
        village::Village *vill, void *tick, void * blockSource
) {
    original(vill, tick, blockSource);
    village::villageHelper.insert(vill);
}

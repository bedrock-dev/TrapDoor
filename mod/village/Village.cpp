//
// Created by xhy on 2020/8/25.
//
#include "Village.h"
#include "tools/Message.h"
#include "graphics/Particle.h"
#include "tools/MsgBuilder.h"
#include "entity/Player.h"
#include "TrapdoorMod.h"
#include "BDSMod.h"

using namespace SymHook;
//village tick

namespace mod {


    namespace {
        const size_t BOUND_OFFSET = 104;
        const size_t POPULATION_OFFSET = 22;
        const size_t GOLEM_NUM_OFFSET = 30;
    }


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

    //check can actor iron golem
    bool Village::canSpawnIronGolem() {
        auto population = getPopulation();
        auto workedNum = getWorkedVillagerNum();
        auto golemNum = getIronGolemNum();
        auto bedNum = getBedPOICount();
        int maxValue = 20 > population ? 20 : population;
        return (float) workedNum > population * 0.75 && golemNum < population / 10 && bedNum > maxValue;
    }

    //get village center
    trapdoor::BlockPos Village::getCenter() {
        return {
                (*((float *) this + BOUND_OFFSET + 3) + *((float *) this + BOUND_OFFSET)) / 2,
                (*((float *) this + BOUND_OFFSET + 4) + *((float *) this + BOUND_OFFSET + 1)) / 2,
                (*((float *) this + BOUND_OFFSET + 5) + *((float *) this + BOUND_OFFSET + 2)) / 2,
        };
    }

    //get village bounds
    //todo rewrite this
    trapdoor::AABB Village::getBounds() {
        return *reinterpret_cast<trapdoor::AABB *>((float *) this + BOUND_OFFSET);
    }

    //get village radius
    float Village::getRadius() {
        return SYM_CALL(
                float(*)(Village * ),
                MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ,
                this
        );
    }

    void VillageHelper::clear() {
        villageList.clear();
    }

    void VillageHelper::insert(Village *village) {
        villageList.insert(village);
    }

    void VillageHelper::draw() {
        if (this->enableShow) {
            std::string centerParticleType = "minecraft:heart_particle";
            for (auto village:villageList) {
                if (village) {
                    auto center = village->getCenter().toVec3() + trapdoor::Vec3(0.5f, 0.8f, 0.5f);
                    auto bounds = village->getBounds();
                    spawnRectangleParticle(bounds);
                    spawnParticle(center, centerParticleType);
                }
            }
        }
    }

    void VillageHelper::list(trapdoor::Actor *player) {
        trapdoor::MessageBuilder builder;
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
                        .num((int) village->canSpawnIronGolem())
                        .text(" ")
                        .aabb(aabb)
                        .text("\n");
            }
        }
        builder.send(player);
        //  builder.send();
    }

    void VillageHelper::tick() {
        if (gameTick % 40 == 0) {
            //todo clear village and draw village;
            this->draw();
            this->clear();
        }
        this->gameTick = (this->gameTick + 1) % 80;
    }
}

THook(
        void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
        mod::Village *vill, void *tick, void * blockSource
) {
    //village tick
    original(vill, tick, blockSource);
    trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()->getVillageHelper().insert(vill);
    // village::villageHelper.insert(vill);
}


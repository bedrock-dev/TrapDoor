//
// Created by xhy on 2020/8/25.
//
#include "Village.h"
#include "tools/Message.h"
#include "graphics/Particle.h"
#include "tools/MsgBuilder.h"
#include "player/Player.h"
#include "TrapdoorMod.h"
#include "BDSMod.h"
#include "graphics/Graphics.h"
#include <random>

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
    trapdoor::Vec3 Village::getCenter() {
        return this->getBounds().getCenter();
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

    trapdoor::AABB Village::getPOIRange() {
        auto bounds = this->getBounds();
        return trapdoor::AABB(bounds.p1 - Vec3(64, 64, 64), bounds.p2 + Vec3(64, 64, 64));
    }

    trapdoor::AABB Village::getGolemSpawnArea() {
        auto center = this->getCenter();
        return trapdoor::AABB(center - Vec3(8, 3, 8), center + Vec3(8, 3, 8));
    }

    void VillageHelper::clear() {
        villageList.clear();
    }

    void VillageHelper::insert(const VillageWithColor &vw) {
        villageList.insert(vw);
    }

    void VillageHelper::draw() {
        std::string centerParticleType = "minecraft:heart_particle";
        for (auto vw:villageList) {
            auto village = vw.village;
            if (village) {
                if (this->showBounds)
                    trapdoor::spawnRectangleParticle(village->getBounds(), trapdoor::GRAPHIC_COLOR::BLUE);
                if (this->showVillageCenter)
                    trapdoor::spawnParticle(village->getCenter() + Vec3(0.5f, 0.9f, 0.5f), centerParticleType);
                if (this->showGolemSpawnArea)
                    trapdoor::spawnRectangleParticle(village->getGolemSpawnArea(), trapdoor::GRAPHIC_COLOR::GREEN);
                if (this->showPOIRange)
                    trapdoor::spawnRectangleParticle(village->getPOIRange(), trapdoor::GRAPHIC_COLOR::YELLOW);
            }
        }
    }


    void VillageHelper::list(trapdoor::Actor *player) {
        trapdoor::MessageBuilder builder;
        builder.text("here are all the ticking villages:\n");
        int i = 0;
        for (auto vw : villageList) {
            auto village = vw.village;
            if (village) {
                i++;
                auto aabb = village->getBounds();
                builder.num(i).text(": ")
                        .pos(village->getCenter().toBlockPos())
                        .text("r:")
                        .num(village->getRadius())
                        .text(" p:")
                        .num(village->getWorkedVillagerNum())
                        .text("/")
                        .num(village->getPopulation())
                        .text(" g:")
                        .num(village->getIronGolemNum())
                        .text(" b:")
                        .num(village->getBedPOICount())
                        .text(" s:")
                        .num((int) village->canSpawnIronGolem())
                        .text(" [")
                        .pos(aabb.p1.toBlockPos())
                        .text("-")
                        .pos(aabb.p2.toBlockPos())
                        .text("]\n");
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

    bool VillageWithColor::operator<(const VillageWithColor &rhs) const {
        return this->village < rhs.village;
    }

    //todo: repair this bug
    void VillageWithColor::setRandomColor() {
        using COLOR = trapdoor::GRAPHIC_COLOR;
        static COLOR colorList[5] = {
                COLOR::WHITE,
                COLOR::GREEN,
                COLOR::RED,
                COLOR::BLUE,
                COLOR::YELLOW
        };
        // static std::random_device rd;
        // static std::mt19937 gen(rd());
        //    this->color = colorList[rand() % 5];
    }
}

THook(
        void, MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
        mod::Village *vill, void *tick, void * blockSource
) {
    //village tick
    original(vill, tick, blockSource);
    mod::VillageWithColor vw{vill, trapdoor::GRAPHIC_COLOR::GREEN};
    trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()->getVillageHelper().insert(vw);
    // village::villageHelper.insert(vill);
}


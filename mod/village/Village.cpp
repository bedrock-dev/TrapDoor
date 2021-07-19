//
// Created by xhy on 2020/8/25.
//
#include "Village.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "graphics/Graphics.h"
#include "graphics/Particle.h"
#include "player/Player.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include <random>

using namespace SymHook;

// village tick
#include "BDSMod.h"
#include "POIInstance.h"
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "lib/Remotery.h"
#include "tools/MsgBuilder.h"
#include "world/Level.h"
#include <array>
#include <utility>
#include <vector>
namespace mod {

namespace {
const size_t BOUND_OFFSET = 104;
// from Village::_trySpawnDefenderDwellers
const size_t POPULATION_OFFSET = 22;
// from Village::_trySpawnDefenderDwellers
const size_t GOLEM_NUM_OFFSET = 30;
// from Village::_trySpawnDefenderDwellers
const size_t DWELLER_POI_MAP_OFFSET = 96;

const size_t DWELLER_TICK_MAP_OFFSET = 160;

struct DwellerData {
    uint64_t tick;
    trapdoor::BlockPos pos;
};

// typedef std::vector<std::weak_ptr<mod::POIInstance>> DwellerData;
typedef std::array<std::unordered_map<trapdoor::ActorUniqueID, DwellerData,
                                      trapdoor::ActorUniqueIDHash>,
                   4>
    DwellerTickMapType;

typedef std::unordered_map<trapdoor::ActorUniqueID,
                           std::array<std::weak_ptr<POIInstance>, 3>,
                           std::hash<ActorUniqueID>>
    DwellerPOIMapType;

DwellerPOIMapType *getDwellerPOIMap(Village *v) {
    return reinterpret_cast<DwellerPOIMapType *>((char *)v +
                                                 DWELLER_POI_MAP_OFFSET);
}

DwellerTickMapType *getDwellerTicklMap(Village *v) {
    return reinterpret_cast<DwellerTickMapType *>((char *)v +
                                                  DWELLER_TICK_MAP_OFFSET);
}

} // namespace

// get village population
int Village::getPopulation() {
    return (int)*((int64_t *)this + POPULATION_OFFSET);
}

// get village owned iron golem num
int Village::getIronGolemNum() {
    return (int)*((int64_t *)this + GOLEM_NUM_OFFSET);
}

// get village owned bed poi count(max is villager num + 32)
int Village::getBedPOICount() {
    return SYM_CALL(int (*)(Village *),
                    MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ,
                    this);
}

// get worked villager num
int Village::getWorkedVillagerNum() {
    // from Village::_trySpawnDefenderDwellers
    auto timeOfDay = *(reinterpret_cast<int64_t *>(this) + 60) - 24000;
    auto begin = *(reinterpret_cast<int64_t *>(this) + 85);
    auto end = *(reinterpret_cast<int64_t *>(this) + 86);
    int num;
    for (num = 0; begin != end; begin += 16) {
        if (*(int64_t *)(begin + 8) > timeOfDay)
            ++num;
    }
    return num;
}

// check can actor iron golem
bool Village::canSpawnIronGolem() {
    auto population = getPopulation();
    auto workedNum = getWorkedVillagerNum();
    auto golemNum = getIronGolemNum();
    auto bedNum = getBedPOICount();
    int maxValue = 20 > population ? 20 : population;
    return (float)workedNum > population * 0.75 && golemNum < population / 10 &&
           bedNum > maxValue;
}

// get village center
trapdoor::Vec3 Village::getCenter() { return this->getBounds().getCenter(); }

// get village bounds
trapdoor::AABB Village::getBounds() {
    return *reinterpret_cast<trapdoor::AABB *>((float *)this + BOUND_OFFSET);
}

// get village radius
float Village::getRadius() {
    return SYM_CALL(float (*)(Village *),
                    MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ,
                    this);
}

trapdoor::AABB Village::getPOIRange() {
    auto bounds = this->getBounds();
    return trapdoor::AABB(bounds.p1 - Vec3(64, 64, 64),
                          bounds.p2 + Vec3(64, 64, 64));
}

trapdoor::AABB Village::getGolemSpawnArea() {
    auto center = this->getCenter();
    return trapdoor::AABB(center - Vec3(8, 3, 8), center + Vec3(8, 3, 8));
}

void Village::showVillagerStatus(int vIdx) {
    auto *map = getDwellerPOIMap(this);
    int idx = 1;
    const char *icons[3] = {"☾", "⍾", "☕"};
    for (auto &villager : *map) {
        auto actor = trapdoor::bdsMod->fetchEntity(villager.first.uid, false);
        if (actor) {
            trapdoor::MessageBuilder builder;
            builder.textF("[%d] %d", vIdx, idx);
            ++idx;
            for (int index = 0; index < 3; ++index) {
                auto poi = villager.second[index].lock();
                if (poi) {
                    builder.sTextF(MSG_COLOR::GREEN, " %s", icons[index]);
                } else {
                    builder.sTextF(MSG_COLOR::RED, " %s", icons[index]);
                }
            }
            actor->setNameTag(builder.get());
        }
    }
    this->showTimeStamp();
}

//    void Village::showTimeStamp() {
//        auto *dwellerList =
//        reinterpret_cast<std::array<std::unordered_map<trapdoor::ActorUniqueID,
//                uint64_t, trapdoor::ActorUniqueIDHash>, 4> * >((char *) this +
//                152);
//        for (int i = 1; i < 4; i++) {
//            auto dwellers = dwellerList->operator[](i);
//            for (const auto &d:dwellers) {
//                auto actor = trapdoor::bdsMod->fetchEntity(d.first.uid,
//                false); if (actor) {
//                    actor->setNameTag(std::to_string(d.second));
//                }
//            }
//        }
//    }

std::string Village::getDebugInfo() {
    using namespace trapdoor;
    trapdoor::MessageBuilder builder;
    auto pos = this->getCenter().toBlockPos();
    auto minPos = this->getBounds().p1.toBlockPos();
    auto maxPos = this->getBounds().p2.toBlockPos();
    builder.text("Village: ")
        .pos(pos)
        .text("\n- Bounds: ")
        .pos(minPos)
        .text(" , ")
        .pos(maxPos)
        .text("\n")
        .text("- Radius: ")
        .num(this->getRadius())
        .text("\n")
        .text("Dweller: ")
        .sTextF(MSG_COLOR::GREEN, "%d / %d %d\n", getWorkedVillagerNum(),
                getPopulation(), getIronGolemNum())
        .text("POIS:\n      Bed          |          Work       |\n");
    auto *map = getDwellerPOIMap(this);
    bool existAlarm = false;
    for (auto &villager : *map) {
        for (int index = 0; index < 3; ++index) {
            if (index == 0) {
                builder.text("|");
            }

            auto poi = villager.second[index].lock();
            if (index == 1) {
                if (poi)
                    existAlarm = true;
                continue;
            }
            if (poi) {
                builder
                    .sTextF(MSG_COLOR::WHITE, " %-4d  %-4d  %-4d ",
                            poi->poiPos.x, poi->poiPos.y, poi->poiPos.z)
                    .text("|");
            } else {
                builder.sText("       (null)        ", MSG_COLOR::GRAY)
                    .text("|");
            }
            if (index == 2) {
                builder.text("\n");
            }
        }
    }
    builder.textF("Alarm:  %d", existAlarm);
    return builder.get();
}

bool Village::printVillagerInfo(trapdoor::Actor *player, trapdoor::Actor *v) {
    // auto *map = getDwellerPOIMap(this);
    // for (auto &villager : *map) {
    //     auto actor = trapdoor::bdsMod->fetchEntity(villager.first.uid,
    //     false); if (actor && v && actor == v) {
    //         trapdoor::MessageBuilder builder;
    //         auto center = this->getCenter().toBlockPos();
    //         builder.textF("center: [%d %d %d]\n", center.x, center.y,
    //         center.z); auto bed = villager.second[0].lock(); auto alarm =
    //         villager.second[1].lock(); auto work = villager.second[2].lock();
    //         if (bed) {
    //             builder.text("Bed position: ").pos(bed->poiPos);
    //         }
    //         if (alarm) {
    //             builder.text("\nAlarm position: ").pos(alarm->poiPos);
    //         }
    //         if (work) {
    //             builder.text("\nWork position: ").pos(work->poiPos);
    //         }
    //         builder.send(player);
    //         return true;
    //     }
    // }
    return false;
}

//这个96是一个POI分配表
void Village::removeAllTags() {
    auto *tickMap = getDwellerTicklMap(this);
    for (auto i : *tickMap) {
        for (auto &v : i) {
            auto actor = trapdoor::bdsMod->fetchEntity(v.first.uid, false);
            if (actor) {
                actor->setNameTag("");
            }
        }
    }
}

void Village::showTimeStamp() {
    auto *tickMap = getDwellerTicklMap(this);
    int index = 0;
    for (auto i : *tickMap) {
        for (auto &v : i) {
            auto actor = trapdoor::bdsMod->fetchEntity(v.first.uid, false);
            if (actor) {
                if (index == 0) {
                    actor->setNameTag(actor->getNameTag() + " " +
                                      std::to_string(v.second.tick));
                } else {
                    actor->setNameTag(std::to_string(v.second.tick));
                }
            }
        }

        index++;
    }
}

void VillageHelper::clear() { villageList.clear(); }

void VillageHelper::insert(const VillageWithColor &vw) {
    villageList.insert(vw);
}

void VillageHelper::draw() {
    for (auto vw : villageList) {
        auto village = vw.village;
        if (village) {
            if (this->showBounds)
                trapdoor::spawnRectangleParticle(
                    village->getBounds(), villageHelperConfig.boundColor);
            if (this->showVillageCenter)
                trapdoor::spawnParticle(village->getCenter() +
                                            Vec3(0.5f, 0.9f, 0.5f),
                                        villageHelperConfig.centerParticle);
            if (this->showGolemSpawnArea)
                trapdoor::spawnRectangleParticle(
                    village->getGolemSpawnArea(),
                    villageHelperConfig.spawnColor);

            if (this->showPOIRange)
                trapdoor::spawnRectangleParticle(
                    village->getPOIRange(), villageHelperConfig.poiQueryColor);

            if (this->showDwellerStatus)
                this->showVillagerStatus();
        }
    }
}

void VillageHelper::list(trapdoor::Actor *player) {
    trapdoor::MessageBuilder builder;
    builder.text(LANG("village.info.allVillages"));
    int i = 0;
    for (auto vw : villageList) {
        auto village = vw.village;
        if (village) {
            i++;
            auto aabb = village->getBounds();
            builder.num(i)
                .text(": ")
                .pos(village->getCenter().toBlockPos())
                .text(" r:")
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
                .num((int)village->canSpawnIronGolem())
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
    // rmt_ScopedCPUSample(VILLAGE_TICK, 0)
    if (gameTick % 40 == 0) {
        // todo clear village and draw village;
        this->draw();
        this->clear();
    }
    this->gameTick = (this->gameTick + 1) % 80;
}

void VillageHelper::test() {
    for (auto &v : this->villageList) {
        v.village->test();
    }
}

void VillageHelper::showVillagerStatus() {
    int idx = 0;
    for (auto village : this->villageList) {
        idx++;
        village.village->showVillagerStatus(idx);
    }
}

void VillageHelper::printNearestVillageInfo(trapdoor::Actor *player,
                                            const Vec3 &pos) {
    mod::Village *target = nullptr;
    float maxDistance = 1024;
    for (auto village : this->villageList) {
        auto dis = village.village->getCenter().distanceTo(pos);
        if (dis < maxDistance) {
            target = village.village;
            maxDistance = dis;
        }
    }
    if (target) {
        trapdoor::info(player, target->getDebugInfo());
    } else {
        trapdoor::warning(player, LANG("village.error.noVillage"));
    }
}

void Village::test() {
    // finish
    // auto *tickMap = getDwellerTicklMap(this);
    // for (auto i : *tickMap) {
    //     for (auto &v : i) {
    //         auto actor = trapdoor::bdsMod->fetchEntity(v.first.uid, false);
    //         if (actor) {
    //             actor->setNameTag(std::to_string(v.second.tick));
    //         }
    //     }
    // }
}

void VillageHelper::printDwellerInfo(trapdoor::Actor *player,
                                     trapdoor::Actor *actor) {

    //试图获取居民组件
    auto component = getDwellerComponentFromActor(actor);
    if (!component) {
        trapdoor::warning(player, LANG("village.error.notDweller"));
    } else {
        if (actor->getActorId() == "villager_v2") {
            for (auto villages : this->villageList) {
                if (villages.village->printVillagerInfo(player, actor))
                    return;
            }
            trapdoor::warning(player, LANG("village.error.notDweller"));
        } else {
            auto center = component->getVillageCenter(actor);
            trapdoor::info(player, "[ %d  %d  %d]", center->x, center->y,
                           center->z);
        }
    }
}

void VillageHelper::removeAllNameTag() {
    for (auto vill : this->villageList) {
        vill.village->removeAllTags();
    }
}

void VillageHelper::registerCommand(CommandManager &commandManager) {
    commandManager.registerCmd("village", "command.village.desc")
        ->then(ARG("list", "command.village.list.desc", NONE,
                   { this->list(player); }))
        ->then(ARG("b", "command.village.b.desc", BOOL,
                   {
                       this->setShowBound(holder->getBool());
                       info(player, LANG("command.village.b.set"),
                            holder->getBool());
                   }))
        ->then(ARG("p", "command.village.p.desc", BOOL,
                   {
                       this->setShowPOIRange(holder->getBool());
                       info(player, LANG("command.village.p.set"),
                            holder->getBool());
                   }))
        ->then(ARG("s", "command.village.s.desc", BOOL,
                   {
                       this->setShowGolemSpawnArea(holder->getBool());
                       info(player, LANG("command.village.s.set"),
                            holder->getBool());
                   }))
        ->then(ARG("c", "command.village.c.desc", BOOL,
                   {
                       this->setShowVillageCenter(holder->getBool());
                       info(player, LANG("command.village.c.set"),
                            holder->getBool());
                   }))
        ->then(ARG("v", "command.village.v.desc", BOOL,
                   {
                       this->setShowDwellerStatus(holder->getBool());
                       info(player, LANG("command.village.v.set"),
                            holder->getBool());
                   }))

        ->then(
            ARG("n", "command.village.n.desc", NONE,
                { this->printNearestVillageInfo(player, *player->getPos()); }))

        ->then(ARG("test", "???", NONE, {
            //   trapdoor::warning(player, "you are not developer");
            this->test();
        }));
}

bool VillageWithColor::operator<(const VillageWithColor &rhs) const {
    return this->village < rhs.village;
}

} // namespace mod

THook(
    void,
    MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z,
    mod::Village *vill, void *tick, void *blockSource) {
    // village tick
    original(vill, tick, blockSource);
    mod::VillageWithColor vw{vill, trapdoor::GRAPHIC_COLOR::GREEN};
    trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()->getVillageHelper().insert(
        vw);
    // village::villageHelper.insert(vill);
}

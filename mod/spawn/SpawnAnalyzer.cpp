////
//// Created by xhy on 2021/1/1.
////
//
//#include "SpawnAnalyzer.h"
//#include "entity/Actor.h"
//#include "lib/SymHook.h"
//#include "lib/mod.h"
//#include "tools/Message.h"
//#include "TrapdoorMod.h"
//#include "tools/MsgBuilder.h"
//#include <map>
//
//namespace mod {
//
//
//    void SpawnAnalyzer::start(trapdoor::Actor *player) {
//        if (this->inAnalyzing) {
//            trapdoor::warning(player, "生物生成分析器在运行中");
//        } else {
//            this->gameTick = 0;
//            this->spawnData.clear();
//            inAnalyzing = true;
//            trapdoor::info(player, "生物生成分析器已经开始,生物生成分析器数据已经被自动清空");
//        }
//    }
//
//    void SpawnAnalyzer::end(trapdoor::Actor *player) {
//        if (!this->inAnalyzing) {
//            trapdoor::warning(player, "生物生成分析器没有在运行");
//        } else {
//            inAnalyzing = false;
//            trapdoor::info(player, "生物生成分析器已经停止运行");
//        }
//    }
//
//    void SpawnAnalyzer::addMobData(const SpawnAnalyzer::MobSpawnInfo &info) {
//        this->spawnData.push_back(info);
//    }
//
//    void SpawnAnalyzer::clearData(trapdoor::Actor *player) {
//        this->gameTick = 0;
//        this->spawnData.clear();
//        trapdoor::info(player, "数据已经清空");
//    }
//
//    void SpawnAnalyzer::printSimpleData(trapdoor::Actor *player, const std::string &typePatten) const {
//        trapdoor::MessageBuilder builder;
//        std::map<std::string, int> successSurface;
//        std::map<std::string, int> successUnderGround;
//        std::map<std::string, int> failSurface;
//        std::map<std::string, int> failUnderGround;
//        std::map<std::string, int> unSuccessData;
//
//        int successSNum = 0, successUNum = 0, failSNum = 0, failUNum = 0;
//        for (const auto &data:this->spawnData) {
//            if (data.isSurface) {
//                if (data.success) {
//                    successSurface[data.type]++;
//                    successSNum++;
//                } else {
//                    failSurface[data.type]++;
//                    failSNum++;
//                }
//            } else {
//                if (data.success) {
//                    successUnderGround[data.type]++;
//                    successUNum++;
//                } else {
//                    failUnderGround[data.type]++;
//                    failUNum++;
//                }
//            }
//        }
//        int successTotal = successSNum + successUNum;
//        int failTotal = failSNum + failUNum;
//        builder.textF("total %d success, %d fail (%.2f %%%%)\n", successTotal, failTotal,
//                      successTotal * 100.0 / (successTotal + failTotal)).
//                        text("----------Surface----------\n")
//                .textF("%d success %d fail (%.2f %%%%)\n", successSNum, failSNum,
//                       successSNum * 100.0 / (successSNum + failSNum));
//        for (const auto &data:successSurface) {
//            int failNum = failSurface[data.first];
//            builder.text(" - ").text(data.first).text("    ").num(data.second).text("/").num(
//                            failNum + data.second).text(
//                            "(")
//                    .num(data.second * 100 / (failNum + data.second)).text("%%%%)\n");
//        }
//
//        builder.text("----------Underground----------\n")
//                .textF("%d success %d fail (%.2f%%%%)\n", successUNum, failUNum,
//                       successUNum * 100.0 / (successUNum + failUNum));
//
//        for (const auto &data:successUnderGround) {
//            int failNum = failUnderGround[data.first];
//            builder.text(" - ").text(data.first).text("    ").num(data.second).text("/").num(
//                            failNum + data.second).text(
//                            "(")
//                    .num(data.second * 100 / (failNum + data.second)).text("%%%%)\n");
//        }
//        builder.send(player);
//    }
//
//    void SpawnAnalyzer::printSpeedGraph(trapdoor::Actor *player, size_t freq) const {
//        //这里本想打印速度曲线的，不想做了
//    }
//}
//
//using namespace SymHook;


//THook(
//        bool,
//        MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z,
//        void *spawner,
//        trapdoor::BlockSource *bs,
//        trapdoor::ActorDefinitionIdentifier *actorId,
//        trapdoor::Actor *actor,
//        trapdoor::Vec3 *pos,
//        bool naturalSpawn,
//        bool surface,
//        bool fromSpawner
//) {
//    if (!naturalSpawn || fromSpawner) {
//        return original(spawner, bs, actorId, actor, pos, naturalSpawn, surface, fromSpawner);
//    } else {
//        auto success = original(spawner, bs, actorId, actor, pos, naturalSpawn, surface, fromSpawner);
//        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
//        if (modInstance->getSpawnAnalyzer().isRunning()) {
//            mod::SpawnAnalyzer::MobSpawnInfo info{
//                    modInstance->getSpawnAnalyzer().getTick(),
//                    actorId->getName(),
//                    {pos->x, pos->y, pos->z},
//                    surface,
//                    success
//            };
//            modInstance->getSpawnAnalyzer().addMobData(info);
//        }
//        return success;
//    }
//}


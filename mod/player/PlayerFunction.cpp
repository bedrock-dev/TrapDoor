//
// Created by xhy on 2021/1/3.
//
#include "entity/Actor.h"
#include "graphics/Graphics.h"
#include "PlayerFunction.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "graphics/BlockPos.h"
#include "graphics/Particle.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include "world/Biome.h"
#include "block/CircuitComponent.h"
#include "world/Dimension.h"

namespace mod {
    void PlayerFunction::tick() {
        if (gameTick % 20 == 0) {
            auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
            modInstance->getLevel()->forEachPlayer([&](trapdoor::Actor *player) {
                if (this->enableShowChunk[player->getNameTag()]) {
                    drawChunkBound(player);
                }
                //add other functions here
            });
        }
        this->gameTick = (this->gameTick + 1) % 40;
    }


    void PlayerFunction::drawChunkBound(trapdoor::Actor *player) {
        int dimensionID = player->getDimensionID();
        auto playerPos = player->getPos()->toBlockPos();
        auto p = playerPos.toChunkPos();
        trapdoor::spawnChunkSurfaceParticle(p, dimensionID);
    }

    void PlayerFunction::printDebugInfo(trapdoor::Actor *player) {
        MessageBuilder builder;
        auto position = player->getPos();
        auto playerBlockPos = position->toBlockPos();
        auto chunkPos = playerBlockPos.toChunkPos();
        auto inChunkOffset = playerBlockPos.InChunkOffset();
        auto inSlimeChunk = chunkPos.isSlimeChunk();
        Vec3 viewVec{};
        player->getViewActor(&viewVec, 1);
        auto biome = player->getBlockSource()->getBiome(&playerBlockPos);
        auto name = biome->getBiomeName();


        auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
        auto modInfo = modInstance->modeInfo;


//        std::string MinecraftVersion = format("Minecraft Bedrock(BDS) %s  (%s)\n\n", minecraftVersion,
//                                              trapDoorVersion);
        std::string xyz = format("XYZ: %.2f / %.2f / %.2f\n", position->x, position->y, position->z);
        std::string block = format("Block: %d %d %d\n", playerBlockPos.x, playerBlockPos.y, playerBlockPos.z);
        std::string chunk = "Chunk: " + inChunkOffset.toString() + " in " + chunkPos.toString() + "\n";
        std::string facing = "Facing: " + viewVec.toDirString();
        facing += format("(%.2f / %.2f / %.2f)\n", viewVec.x, viewVec.y, viewVec.z);
        std::string biomeString = format("Biome: minecraft:%s (%d)\n", name.c_str(), biome->getBiomeType());
        std::string dimString = format("Dimension: %s (%d)\n", player->getDimensionName().c_str(),
                                       player->getDimensionID());
        builder.textF("Minecraft BDS %s (%s)\n", modInfo.minecraftVersion.c_str(), modInfo.modVersion.c_str())
                .text(xyz)
                .text(block);
        if (inSlimeChunk) {
            builder.sText(chunk, MSG_COLOR::GREEN);
        } else {
            builder.text(chunk);
        }
        builder.text(facing).text(biomeString).text(dimString)
                .send(player);
    }

    void PlayerFunction::printRedstoneInfo(trapdoor::Actor *player, BlockPos &pos) {
        if (!this->enableRedstoneHelper[player->getNameTag()])return;
        auto graph = player->getDimension()->getGraph();
        auto component = graph->getBaseCircuitComponent(&pos);
        if (!component) {
            trapdoor::warning(player, "这不是一个红石原件");
            return;
        }
        component->basePrint(graph, player);
    }

    void PlayerFunction::registerSelfCommand(trapdoor::CommandManager &commandManager) {
        //todo
    }

    void PlayerFunction::broadcastSimpleInfo(trapdoor::Actor *player) {
        auto pos = player->getPos()->toBlockPos();
        auto dim = (DimensionType) player->getDimensionID();
        trapdoor::MessageBuilder builder;
        int nX = 0, nZ = 0;
        builder.text(player->getNameTag()).text(" @ ");
        switch (dim) {
            case OverWorld:
                builder.sText("主世界", MSG_COLOR::GREEN);
                nX = pos.x / 8, nZ = pos.z / 8;
                break;
            case Nether:
                builder.sText("下界", MSG_COLOR::RED);
                nX = pos.x * 8, nZ = pos.z * 8;
                break;
            case TheEnd:
                builder.sText("末地", MSG_COLOR::YELLOW);
                break;
        }

        builder.sTextF(MSG_COLOR::AQUA, "  [%d %d %d]  ", pos.x, pos.y, pos.z);
        if (dim == OverWorld) {
            builder.text("==>  ").sText("下界", MSG_COLOR::RED).sTextF(MSG_COLOR::AQUA, " [%d %d]", nX, nZ);
        }
        if (dim == Nether) {
            builder.text("==>  ").sText("主世界", MSG_COLOR::GREEN).sTextF(MSG_COLOR::AQUA, " [%d %d]", nX, nZ);
        }
        builder.broadcast();
    }

    void PlayerFunction::listAllPlayers(trapdoor::Actor *player) {
        trapdoor::MessageBuilder builder;
        trapdoor::bdsMod->getLevel()->forEachPlayer([&](trapdoor::Actor *actor) {
            auto pos = actor->getPos()->toBlockPos();
            builder.textF("%s @ %s => [%d %d %d]\n", actor->getNameTag().c_str(), actor->getDimensionName().c_str(),
                          pos.x,
                          pos.y,
                          pos.z
            );
        });
        builder.send(player);
    }

    void MeasureData::setPosition2(const BlockPos &pos, trapdoor::Actor *player) {
        if (!this->enableMeasure)return;
        this->pos2 = pos;
        this->hasSetPos2 = true;
        this->trySendDistanceInfo(player);
    }

    void MeasureData::setPosition1(const BlockPos &pos, trapdoor::Actor *player) {
        if (!this->enableMeasure)return;
        this->pos1 = pos;
        this->hasSetPos1 = true;
        this->trySendDistanceInfo(player);
    }

    void MeasureData::trySendDistanceInfo(trapdoor::Actor *player) const {
        trapdoor::MessageBuilder builder;
        if (hasSetPos1 && !hasSetPos2) {
            builder.text("set p1 ").pos(this->pos1).send(player);
        } else if (hasSetPos2 && !hasSetPos1) {
            builder.text("set p2 ").pos(this->pos2).send(player);
        } else if (hasSetPos1 && hasSetPos2) {
            float distance = pos1.distanceTo(pos2);
            int distance2 = abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y) + abs(pos1.z - pos2.z);
            trapdoor::BlockPos pos = {pos1.x, pos2.y, pos1.z};
            float distance3 = pos.distanceTo(pos2);
            int distance4 = abs(pos1.x - pos2.x) + abs(pos1.z - pos2.z);

            builder.pos(pos1).text(" -").pos(pos2).text("\n - ")
                    .num(distance).text(" ").num(distance2).text("\n - ")
                    .num(distance3).text(" ").num(distance4).send(player);
        }
    }


}


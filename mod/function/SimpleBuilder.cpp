//
// Created by xhy on 2021/1/5.
//

#include "SimpleBuilder.h"

#include "block/Block.h"
#include "block/BlockSource.h"
#include "entity/Actor.h"
#include "graphics/BlockPos.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"

namespace mod {

    bool SimpleBuilder::preCheck(trapdoor::Actor *player, size_t radius) const {
        if (!player) {
            return false;
        }
        if (!this->enable) {
            info(player, "builder未开启");
            return false;
        }
        if (radius > this->maxCircleRadius) {
            info(player, "半径过大(必须<= 30000000)");
            return false;
        }
        return true;
    }
    void SimpleBuilder::buildCircle(trapdoor::Actor *player, size_t radius,
                                    bool hollow) const {
        if (!this->preCheck(player, radius)) {
            return;
        }
        trapdoor::BlockPos standPos = player->getStandPosition();
        auto block = player->getBlockSource()->getBlock(standPos.x, standPos.y,
                                                        standPos.z);
        trapdoor::BlockPos pos = standPos;
        //  printf("%d %d %d %s", pos.x,pos.y,pos.z, block->getName().c_str());
        float R = radius;
        R += 0.5;
        int X, Y, p;
        X = 0;
        Y = R;
        p = 3 - 2 * R;
        if (!hollow) {
            for (; X <= Y; X++) {
                for (int Yi = X; Yi <= Y; Yi++) {
                    pos.x = standPos.x + X;
                    pos.z = standPos.z + Yi;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.z = standPos.z - Yi;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.x = standPos.x - X;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.z = standPos.z + Yi;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.x = standPos.x + Yi;
                    pos.z = standPos.z + X;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.z = standPos.z - X;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.x = standPos.x - Yi;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.z = standPos.z + X;
                    player->getBlockSource()->setBlock(&pos, block);
                }
                if (p >= 0) {
                    p += 4 * (X - Y) + 10;
                    Y--;
                } else {
                    p += 4 * X + 6;
                }
            }
        } else {
            for (; X <= Y; X++) {
                pos.x = standPos.x + X;
                pos.z = standPos.z + Y;
                player->getBlockSource()->setBlock(&pos, block);
                pos.z = standPos.z - Y;
                player->getBlockSource()->setBlock(&pos, block);
                pos.x = standPos.x - X;
                player->getBlockSource()->setBlock(&pos, block);
                pos.z = standPos.z + Y;
                player->getBlockSource()->setBlock(&pos, block);
                pos.x = standPos.x + Y;
                pos.z = standPos.z + X;
                player->getBlockSource()->setBlock(&pos, block);
                pos.z = standPos.z - X;
                player->getBlockSource()->setBlock(&pos, block);
                pos.x = standPos.x - Y;
                player->getBlockSource()->setBlock(&pos, block);
                pos.z = standPos.z + X;
                player->getBlockSource()->setBlock(&pos, block);
                if (p >= 0) {
                    p += 4 * (X - Y) + 10;
                    Y--;
                } else {
                    p += 4 * X + 6;
                }
            }
        }
    }

    void SimpleBuilder::buildSphere(trapdoor::Actor *player, size_t radius,
                                    bool hollow) const {
        if (!this->preCheck(player, radius)) {
            return;
        }

        trapdoor::BlockPos standPos = player->getStandPosition();
        auto block = player->getBlockSource()->getBlock(standPos.x, standPos.y,
                                                        standPos.z);
        trapdoor::BlockPos pos = standPos;
        float R = radius;
        R += 0.5;
        int Radius = (int)ceil(radius);
        float nextXn = 0;
        for (int x = 0; x <= Radius; ++x) {
            float xn = nextXn;
            nextXn = (x + 1) / R;
            float nextYn = 0;
            for (int y = 0; y <= Radius; ++y) {
                float yn = nextYn;
                nextYn = (y + 1) / R;
                float nextZn = 0;
                for (int z = 0; z <= Radius; ++z) {
                    float zn = nextZn;
                    nextZn = (z + 1) / R;
                    if (xn * xn + yn * yn + zn * zn > 1) continue;
                    if (hollow) {
                        if (nextXn * nextXn + yn * yn + zn * zn <= 1 &&
                            xn * xn + nextYn * nextYn + zn * zn <= 1 &&
                            xn * xn + yn * yn + nextZn * nextZn <= 1) {
                            continue;
                        }
                    }
                    pos.x = standPos.x + x;
                    pos.y = standPos.y + y;
                    pos.z = standPos.z + z;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.y = standPos.y - y;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.z = standPos.z - z;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.x = standPos.x - x;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.y = standPos.y + y;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.x = standPos.x + x;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.x = standPos.x - x;
                    pos.z = standPos.z + z;
                    player->getBlockSource()->setBlock(&pos, block);
                    pos.y = standPos.y - y;
                    player->getBlockSource()->setBlock(&pos, block);
                }
            }
        }
    }

    void SimpleBuilder::chunksFill(trapdoor::Actor *player, size_t size,
                                   bool hollow) const {
        if (!this->preCheck(player, size)) {
            return;
        }

        auto standPos = player->getStandPosition();
        auto block = player->getBlockSource()->getBlock(standPos.x, standPos.y,
                                                        standPos.z);
        auto chunkPos = standPos.toChunkPos();
        auto cx = chunkPos.x * 16;
        auto cz = chunkPos.z * 16;
        for (auto i = 0; i < 16; i++) {
            for (auto j = 0; j < 16; j++) {
                trapdoor::BlockPos p = {cx + i, standPos.y, cz + j};
                player->getBlockSource()->setBlock(&p, block);
            }
        }
    }

    void SimpleBuilder::registerDrawCommand(CommandManager &commandManager) {
        using namespace trapdoor;
        commandManager.registerCmd("draw", "command.draw.desc")
            ->then(ARG("ci", "command.draw.ci.desc", INT,
                       {
                           auto radius = holder->getInt();
                           bool hollow = holder->getInt() < 0;
                           if (radius < 0) radius = -radius;
                           buildCircle(player, radius, hollow);
                       }))
            ->then(ARG("sp", "command.draw.sp.desc", INT,
                       {
                           auto radius = holder->getInt();
                           bool hollow = holder->getInt() < 0;
                           if (radius < 0) radius = -radius;
                           buildSphere(player, radius, hollow);
                       }))
            ->then(ARG("ch", "command.draw.ch.desc", NONE,
                       {
                           //  auto radius = holder->getInt();
                           //  bool hollow = holder->getInt() < 0;
                           //  if (radius < 0)
                           //      radius = -radius;
                           chunksFill(player, 0, false);
                       }))
            ->then(ARG("mr", "command.draw.mr.desc", INT, {
                auto radius = holder->getInt();
                if (radius < 0) {
                    error(player, "参数不合法(必须>=1)");
                } else {
                    info(player, "已设置最大半径为%d", radius);
                    setMaxRadius(radius);
                }
            }));
    }

}  // namespace mod

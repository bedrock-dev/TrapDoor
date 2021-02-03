//
// Created by xhy on 2021/2/2.
//

#include "SimpleLitematica.h"
#include "trapdoor.h"

namespace mod {

    namespace {
        SimpleLitematica::FileHeader *
        createHelder(uint8_t mcVersion, uint8_t formatVersion, const trapdoor::BlockPos &pos, uint32_t blockNum) {
            if (pos.x < 0 || pos.y < 0 || pos.z < 0)
                return nullptr;
            auto *header = new SimpleLitematica::FileHeader;
            header->dx = (uint32_t) pos.x;
            header->dy = (uint32_t) pos.y;
            header->dz = (uint32_t) pos.z;
            header->mcVersion = mcVersion;
            header->forMatVersion = formatVersion;
            header->blockNum = blockNum;
            strcpy(header->magic, "hhhxiao");
            return header;
        }
    }

    /*
     * 从选取中收集方块信息并存入数组
     */
    bool SimpleLitematica::collectBlockData(trapdoor::Actor *player) {
        if (!this->selectRegion.hasSet()) {
            trapdoor::warning(player, "请先确定选区域");
            return false;
        }
        this->copiedBlockData.clear();
        auto blockSource = player->getBlockSource();
        auto pMin = this->selectRegion.getBoundingBox().minPos;
        auto pMax = this->selectRegion.getBoundingBox().maxPos;
        for (int i = pMin.x; i <= pMax.x; i++) {
            for (int j = pMin.y; j <= pMax.y; j++) {
                for (int k = pMin.z; k <= pMax.z; k++) {
                    trapdoor::BlockPos p(i, j, k);
                    auto block = blockSource->getBlock(p);
                    auto name = block->getName();
                    if (name != "minecraft:air") {
                        BlockData data;
                        data.x = i - pMin.x;
                        data.y = j - pMin.y;
                        data.z = k - pMin.z;
                        memcpy(data.name, name.c_str(), 128);
                        data.variant = block->getVariant();
                        this->copiedBlockData.push_back(data);
                    }
                }
            }
        }
        this->vecPos = {pMax.x - pMin.x, pMax.y - pMin.y, pMax.z - pMin.z};
        trapdoor::info(player, "已采集地形数据");
        hasData = true;
        this->printNeedBlocks(player, 0);
        return true;
    }

    void SimpleLitematica::tick() {
        this->selectRegion.tick(GRAPH_COLOR::BLUE);
        if (this->hasPlaced) {
            //   auto color = this->hasFixed ? GRAPH_COLOR::RED : GRAPH_COLOR::YELLOW;
            auto color = GRAPH_COLOR::RED;
            this->placeRegion.tick(color);
        }
        //  this->tickPosStatus();
    }

    void SimpleLitematica::registerCommand(CommandManager &commandManager) {
        using namespace trapdoor;
        commandManager.registerCmd("test", "建筑相关")
                        //     ->then(ARG("copy", "复制地形数据", NONE, { this->collectBlockData(player); }))
                ->then(ARG("save", "存储到本地", STR, { this->saveData(player, holder->getString()); }))
                ->then(ARG("load", "加载本地文件", STR, { this->readData(player, holder->getString()); }))
                ->then(ARG("place", "放置地形", NONE, { this->placeBlockData(player); }))
                ->then(ARG("lock", "锁定放置位置", BOOL, {}))
                ->then(ARG("c", "检查当前层的放置情况", NONE, { this->checkStatus(player); }))
//                ->then(ARG("notice", "开关放置提醒", BOOL, {}))
//                ->then(ARG("log", "订阅", STR, {}))
//                ->then(ARG("unlog", "取消订阅", STR, {}))
//                ->then(ARG("ol", "显示外框", BOOL, {}))
                ->then(ARG("layer", "分层显示", BOOL, { this->setEnableLayers(holder->getBool()); }))
                ->then(ARG("sl", "向上提高", INT, { this->changeLayer(player, holder->getInt()); }));
    }

    SelectRegion &SimpleLitematica::getSelectRegion() {
        return this->selectRegion;
    }


    void SimpleLitematica::placeBlockData(trapdoor::Actor *player) {
        if (!this->hasData) {
            trapdoor::warning(player, "你还未加载文件或者复制地形数据");
            return;
        }
//        if (this->hasFixed) {
//            trapdoor::warning(player, "位置已经锁定，无法放置地形");
//            return;
//        }
        auto pMin = player->getStandPosition();
        auto pMax = this->vecPos + pMin;
        this->placeRegion.forceSetBoundingBox({pMin, pMax});
        coverDataToLayers(pMin);
        this->hasPlaced = true;
    }

    void SimpleLitematica::printNeedBlocks(trapdoor::Actor *player, int layer) {
        if (!hasData) {
            trapdoor::info(player, "无数据");
            return;
        }
        std::map<std::string, int> map;
        for (const auto &i:this->copiedBlockData) {
            map[i.name]++;
        }
        trapdoor::MessageBuilder builder;
        builder.textF("复制完成,区域大小： [%d %d %d] 一共需要 %zu 个方块",
                      this->vecPos.x + 1, this->vecPos.y + 1, this->vecPos.z + 1,
                      copiedBlockData.size());
        for (auto &i:map)
            builder.textF("\n - %s", i.first.c_str()).text(" : ").num(i.second);
        builder.send(player);
    }

    void SimpleLitematica::setFixed() {
        // this->hasFixed = true;
    }

    void SimpleLitematica::coverDataToLayers(trapdoor::BlockPos &startPos) {
        this->layersPlaceData.clear();
        for (const auto &i:this->copiedBlockData) {
            trapdoor::BlockPos pos(i.x, i.y, i.z);
            auto newPos = pos + startPos;
            this->layersPlaceData[newPos.y][newPos] = i;
        }
    }

    void SimpleLitematica::checkStatus(trapdoor::Actor *player) const {
        if (!this->enableLayers) {
            trapdoor::warning(player, "请先开启按层显示");
            return;
        }
        auto startPos = this->placeRegion.getBoundingBox().minPos;
        int yIndex = startPos.y + this->layerIndex;
        auto layerData = this->layersPlaceData.at(yIndex);
        trapdoor::info(player, "以下是第%d(y = %d)层的情况\n", layerIndex, yIndex);
        trapdoor::BlockSource *bs = player->getBlockSource();
        trapdoor::MessageBuilder builder;
        for (auto &i:layerData) {
            auto *block = bs->getBlock(i.first);
            auto name = block->getName();
            if (name != i.second.name) {
                builder.pos(i.first).text(name).text(" ==> ").text(i.second.name).text("\n");
            } else {
                if (block->getVariant() != i.second.variant) {
                    builder.pos(i.first).num(block->getVariant()).text("  ==> ").num(i.second.variant).text("\n");
                }
            }
        }
        builder.send(player);
    }

    void SimpleLitematica::tickPosStatus() {
        if (!this->hasPlaced || !this->enableLayers)return;
        auto startPos = this->placeRegion.getBoundingBox().minPos;
        int yIndex = startPos.y + this->layerIndex;
        auto layerData = this->layersPlaceData.at(yIndex);
        if (this->gameTick % 20 == 0) {
            this->updateLayerStatus();
            for (const auto &i:layerData) {
                if (i.second.status != PLACE_RIGHT) {
//                    GRAPH_COLOR color = i.second.status == PLACE_ERROR ? GRAPH_COLOR::RED : GRAPH_COLOR::YELLOW;
                    Vec3 v1 = i.first.toVec3();
                    v1 = v1 + Vec3(0.5f, 1.05f, 0.5f);
                    std::string name = "trapdoor:bedrock_up";
                    trapdoor::spawnParticle(v1, name, 0);
//                    v1 = v1 + Vec3(0.5f, 1.0f, 0.0f);
//                    Vec3 v2 = i.first.toVec3();
//                    v2 = v2 + Vec3(0.0f, 1.0f, 0.5f);
//                    trapdoor::spawnLineParticle(v1, trapdoor::FACING::POS_Z, 1.0, color, 0);
//                    trapdoor::spawnLineParticle(v2, trapdoor::FACING::POS_X, 1.0, color, 0);
                }
            }
        }
        this->gameTick = (this->gameTick + 1) % 40;
    }

    void SimpleLitematica::updateLayerStatus() {
        auto startPos = this->placeRegion.getBoundingBox().minPos;
        int yIndex = startPos.y + this->layerIndex;
        auto &layerData = this->layersPlaceData.at(yIndex);
        auto player = trapdoor::bdsMod->getLevel()->getNearestDimensionPlayer(startPos, 0);
        if (!player)return;
        auto bs = player->getBlockSource();
        for (auto &i:layerData) {
            auto *block = bs->getBlock(i.first);
            auto name = block->getName();
            if (name != i.second.name) {
                i.second.status = PLACE_ERROR;
            } else {
                if (block->getVariant() != i.second.variant) {
                    i.second.status = PLACE_WARNING;
                } else {
                    i.second.status = PLACE_RIGHT;
                }
            }
        }
    }

    bool SimpleLitematica::saveData(trapdoor::Actor *player, const std::string &fileName) {
        this->collectBlockData(player);
        const std::string realFileName = fileName + ".tdm";
        FILE *file = fopen(realFileName.c_str(), "wb");
        if (!file) {
            trapdoor::error(player, "文件打开失败！");
            return false;
        }
        auto header = createHelder(16, 0, vecPos, this->copiedBlockData.size());
        if (!header) {
            trapdoor::error(player, "数据错误！");
            return false;
        }
        auto r = fwrite(header, sizeof(SimpleLitematica::FileHeader), 1, file);
        if (r == 0) {
            trapdoor::error(player, "文件头写入失败！");
        }

        for (const auto &data:this->copiedBlockData) {
            r = fwrite(&data, sizeof(SimpleLitematica::BlockData), 1, file);
            if (r == 0) {
                trapdoor::error(player, "数据写入失败！");
            }
        }
        fclose(file);
        delete header;
        trapdoor::info(player, "成功保存到本地");
        return true;
    }


    bool SimpleLitematica::readData(trapdoor::Actor *player, const std::string &fileName) {
        const std::string realFileName = fileName + ".tdm";
        FILE *file = fopen(realFileName.c_str(), "rb");
        if (!file) {
            trapdoor::error(player, "文件读取失败");
            return false;
        }
        SimpleLitematica::FileHeader header{};
        auto r = fread(&header, sizeof(struct SimpleLitematica::FileHeader), 1, file);
        if (r == 0) {
            trapdoor::error(player, "文件头读取失败");
            return false;
        }
        std::string magic(header.magic);
        if (magic != "hhhxiao") {
            trapdoor::error(player, "文件格式校验失败");
            return false;
        }
        this->vecPos = {(int) header.dz, (int) header.dx, (int) header.dz};
        auto size = header.blockNum;
        BlockData data;
        this->copiedBlockData.clear();
        for (int i = 0; i < size; ++i) {
            r = fread(&data, sizeof(struct SimpleLitematica::BlockData), 1, file);
            if (r == 0) {
                trapdoor::error(player, "文件读取失败");
                this->copiedBlockData.clear();
                return false;
            }
            this->copiedBlockData.push_back(data);
        }
        trapdoor::info(player, "文件读取成功");
        hasPlaced = true;
        this->printNeedBlocks(player, 0);
        return true;
    }

}

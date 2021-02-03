//
// Created by xhy on 2021/2/2.
//

#ifndef MOD_SIMPLELITEMATICA_H
#define MOD_SIMPLELITEMATICA_H

#include "SelectRegion.h"
/*
 * 选框
 * 复制
 * 放置
 */

namespace mod {
    class SimpleLitematica {
        enum PlaceStatus : uint8_t {
            PLACE_RIGHT = 0x0,
            PLACE_WARNING = 0x1,
            PLACE_ERROR = 0x2,
        };

        struct BlockData {
            int32_t x{};
            int32_t y{};
            int32_t z{};
            short blockID{};
            unsigned short variant{};
            PlaceStatus status = PlaceStatus::PLACE_ERROR;
        };

        SelectRegion selectRegion; //地形选区
        SelectRegion placeRegion; //放置选区
        trapdoor::BlockPos vecPos; //相对坐标的定点位置
        std::vector<BlockData> copiedBlockData; //地形数据
        bool hasPlaced = false;//是否放置
        bool hasData = false;
        //   bool hasFixed = false;//是否固定
        bool enableLayers = false; //是否分层提示

        std::map<int, std::map<trapdoor::BlockPos, BlockData>> layersPlaceData;
        int layerIndex = 0;
        size_t gameTick;
    private:
        void coverDataToLayers(trapdoor::BlockPos &startPos);

    public:
        void tick();

        void quickPlace(trapdoor::Actor *player);

        SelectRegion &getSelectRegion();

        bool collectBlockData(trapdoor::Actor *player);

        void placeBlockData(trapdoor::Actor *player);

        void setFixed();

        inline void changeLayer(trapdoor::Actor *player, int num) {
            if (!enableLayers) {
                trapdoor::warning(player, "请先开启按层显示");
            }
            this->layerIndex += num;
            if (this->layerIndex > vecPos.y) {
                this->layerIndex = vecPos.y;
                trapdoor::warning(player, "已到达最高层");
            } else if (this->layerIndex < 0) {
                this->layerIndex = 0;
                trapdoor::warning(player, "已到达最低层");
            }
        }

        void setEnableLayers(bool enableLayer) {
            this->enableLayers = enableLayer;
        }

        void registerCommand(trapdoor::CommandManager &commandManager);


        void checkStatus(trapdoor::Actor *player) const;

        void printNeedBlocks(trapdoor::Actor *player, int layer);

        void tickPosStatus();

        void updateLayerStatus();

        bool saveData(trapdoor::Actor *player, const std::string &fileName);

        bool readData(trapdoor::Actor *playe, const std::string &fileName);

        struct FileHeader {
            char magic[8];
            uint8_t forMatVersion;
            uint8_t mcVersion;
            uint32_t dx;
            uint32_t dy;
            uint32_t dz;
            uint32_t blockNum;
        };
    };

}


#endif //MOD_SIMPLELITEMATICA_H

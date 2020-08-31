//
// Created by xhy on 2020/8/29.
//

#ifndef TRAPDOOR_PLAYER_H
#define TRAPDOOR_PLAYER_H

#include "common/BlockPos.h"
#include "common/Common.h"
#include "tools/MathTool.h"
#include "tools/MessageBuilder.h"

class MeasureManager {
    BlockPos pos1{};
    bool pos1Valid = false;
    BlockPos pos2{};
    bool pos2Valid = false;
public:
    MeasureManager() = default;

    void setPos1(BlockPos pos);


    void setPos2(BlockPos pos);

    void print();

    void sendSetInfo(int index);

};


extern MeasureManager measureManager;

#endif //TRAPDOOR_PLAYER_H

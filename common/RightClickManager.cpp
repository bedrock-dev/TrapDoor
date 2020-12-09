//
// Created by xhy on 2020/12/5.
//

#include "RightClickManager.h"

void RightClickManager::registerRightClickBackEvent(const std::string &itemName,
                                                    const RightClickManager::RightClickCallBack &callBack) {
    this->callBackList.insert({itemName, callBack});
}


void RightClickManager::run(Actor *player, const std::string &itemName, const BlockPos &pos, unsigned int face,
                            const Vec3 &offset) {
    auto iter = this->callBackList.find(itemName);
    if (iter == callBackList.end())return;
    iter->second(player, itemName, pos, face, offset);
}


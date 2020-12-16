//
// Created by xhy on 2020/12/5.
//

#ifndef TRAPDOOR_RIGHTCLICKMANAGER_H
#define TRAPDOOR_RIGHTCLICKMANAGER_H

#include <functional>
#include <string>
#include <map>

class Actor;

class BlockPos;

class Vec3;
#define RIGHT_CLICK_EVENT(S)  [](Actor *player, const std::string &itemName, const BlockPos &pos,\
unsigned int face, const Vec3 &offset) {S}

//右键注册，开发中，请无视
class RightClickManager {
public:
    typedef std::function<void(Actor *, const std::string &, const BlockPos &, unsigned int,
                               const Vec3 &)> RightClickCallBack;
private:
    std::map<std::string, RightClickCallBack> callBackList;
public:
    void registerRightClickBackEvent(const std::string &itemName, const RightClickCallBack &&callBack);
    void run(Actor *player, const std::string &itemName, const BlockPos &pos, unsigned int face, const Vec3 &offset);
};


#endif //TRAPDOOR_RIGHTCLICKMANAGER_H

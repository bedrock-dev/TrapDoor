//
// Created by xhy on 2021/1/14.
//

#ifndef MOD_POIINSTANCE_H
#define MOD_POIINSTANCE_H

#include "entity/Actor.h"
#include "graphics/BlockPos.h"

namespace mod {

    enum POIType : int32_t {
        InvalidPOI = -1,
        Bed = 0,
        MeetingArea = 1,
        JobSite = 2,
        Count = 3
    };

    //!这个类不要做任何修改
    class POIInstance {
       public:
        char gap[0x98];
        trapdoor::BlockPos poiPos;   //位置
        uint64_t ownerCount = 0;     //拥有者数量
        uint64_t ownerCapacity = 0;  //容量
        uint64_t weight{};           //权重
        float radius = 0;            //半径
        POIType poiType;             //类型
        std::string soundEvent;
        int16_t arriveFailureCount = 0;  //到达失败的次数
        bool useBoundingBox = true;      //?
    };

}  // namespace mod

#endif  // MOD_POIINSTANCE_H

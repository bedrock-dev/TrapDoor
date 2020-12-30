//
// Created by xhy on 2020/11/13.
//

#ifndef TRAPDOOR_DIMENSION_H
#define TRAPDOOR_DIMENSION_H

namespace trapdoor {

    enum DimensionType {
        OverWorld = 0,
        Nether = 1,
        TheEnd = 2
    };

    class Dimension {
    public:
        void printBaseTypeLimit();
    };
}

#endif //TRAPDOOR_DIMENSION_H

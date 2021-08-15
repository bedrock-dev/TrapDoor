//
// Created by xhy on 2020/11/8.
//

#ifndef TRAPDOOR_BIOME_H
#define TRAPDOOR_BIOME_H

#include <string>

namespace trapdoor {

    class Biome {
       public:
        int getBiomeType();

        std::string getBiomeName();
    };

}  // namespace trapdoor

#endif  // TRAPDOOR_BIOME_H

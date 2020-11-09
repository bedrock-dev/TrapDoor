//
// Created by xhy on 2020/11/8.
//

#ifndef TRAPDOOR_BIOME_H
#define TRAPDOOR_BIOME_H

#include <string>
#include "lib/mod.h"
#include "lib/pch.h"
#include "lib/SymHook.h"

class Biome {

public:
    int getBiomeType();

    std::string getBiomeName();
};


#endif //TRAPDOOR_BIOME_H

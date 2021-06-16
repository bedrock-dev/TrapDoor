//
// Created by xhy on 2020/11/8.
//

#include "Biome.h"

#include "Offset.h"
#include "lib/Loader.h"
namespace trapdoor {

    std::string Biome::getBiomeName() {
        char *str = reinterpret_cast<char *>(this) + off::BIOME_GET_NAME;
        return std::string(str);
    }

    int Biome::getBiomeType() {
        return SymCall("?getBiomeType@Biome@@QEBA?AW4VanillaBiomeTypes@@XZ", int, Biome*)(this);

    }

}
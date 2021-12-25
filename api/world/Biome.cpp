//
// Created by xhy on 2020/11/8.
//

#include "Biome.h"

#include "Offset.h"
#include "lib/SymHook.h"
#include "lib/mod.h"

namespace trapdoor {
    using namespace SymHook;

    std::string Biome::getBiomeName() {
        //return "Unknown";
        char *str = reinterpret_cast<char *>(this) + off::BIOME_GET_NAME;
        return std::string(str);
    }

    int Biome::getBiomeType() {
        return SYM_CALL(int (*)(Biome *), Biome_getBiomeType_bb099b78, this);
    }

}  // namespace trapdoor
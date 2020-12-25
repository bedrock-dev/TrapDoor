//
// Created by xhy on 2020/11/8.
//

#include "Biome.h"


#include "lib/mod.h"
#include "lib/SymHook.h"


namespace trapdoor {
    using namespace SymHook;

    std::string Biome::getBiomeName() {
        char *str = reinterpret_cast<char *>(this) + 8;
        return std::string(str);
    }

    int Biome::getBiomeType() {
        return SYM_CALL(
                int(*)(Biome * ),
                MSSYM_B1QE12getBiomeTypeB1AA5BiomeB2AAA4QEBAB1QE20AW4VanillaBiomeTypesB2AAA2XZ,
                this
        );
    }

}
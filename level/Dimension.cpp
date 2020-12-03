//
// Created by xhy on 2020/11/13.
//

#include "Dimension.h"
#include <cstdio>

void Dimension::printBaseTypeLimit() {
    //from Spawner::_popCapAllows
    char *dim = reinterpret_cast<char *>(this);
    auto *surface = (float *) (dim + 80);
    auto *underground = (float *) (dim + 108);
    for (int i = 0; i < 7; i++) {
        printf("%.3f    %.3f\n", surface[i], underground[i]);
    }
}

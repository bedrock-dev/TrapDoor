//
// Created by xhy on 2021/2/11.
//

#ifndef MOD_CASTHELPER_H
#define MOD_CASTHELPER_H

#include <cstdint>

template <typename T>
/*
 *  [                              ]
 *  |<----bytes---->|
 *  ^               ^
 *  ptr             T
 */
T offset_cast(void *ptr, size_t bytes) {
    return reinterpret_cast<T>(reinterpret_cast<uint8_t *>(ptr) + bytes);
}

#endif  // MOD_CASTHELPER_H

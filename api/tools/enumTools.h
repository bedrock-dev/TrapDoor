//
// Created by xhy on 2020/12/27.
//

#ifndef MOD_ENUMTOOLS_H
#define MOD_ENUMTOOLS_H

#include <cstdlib>
#include <cstdio>
#include <cstdint>

#include <type_traits>

namespace trapdoor {
//from https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int
    namespace details {

        template<typename E>
        using enable_enum_t = typename std::enable_if<std::is_enum<E>::value,
                typename std::underlying_type<E>::type
        >::type;

    }   // namespace details


    template<typename E>
    constexpr inline details::enable_enum_t<E> underlying_value(E e) noexcept {
        return static_cast< typename std::underlying_type<E>::type >( e );
    }


    template<typename E, typename T>
    constexpr inline typename std::enable_if<std::is_enum<E>::value &&
                                             std::is_integral<T>::value, E
    >::type
    to_enum(T value) noexcept {
        return static_cast<E>( value );
    }

} // namespace utils


#endif //MOD_ENUMTOOLS_H

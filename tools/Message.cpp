//
// Created by xhy on 2020/8/25.
//

#include "Message.h"
#include "common/Common.h"
#include <stdarg.h>

using namespace SymHook;
//void warning(const std::string &message) {
//    info("§6%s", message.c_str());
//}
//
//void error(const std::string &message) {
//    info("§c%s", message.c_str());
//}
//
//void info(const std::string &message) {
//    info("%s", message.c_str());
//}


void mcbe_sendMessage(std::string &s, Actor *player) {
    if (!player)return;
    std::vector<std::string> v;
    v.emplace_back("test");
    SYM_CALL(
            void(*)(bool, Actor *, std::string &, std::vector<std::string> &),
            MSSYM_MD5_24be62e9330073695808606844de0d99,
            true, player, s, v);
}


//from https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf

//std::string string_format(const std::string &fmt_str, ...) {
//    int final_n, n = ((int) fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
//    std::unique_ptr<char[]> formatted;
//    va_list ap;
//    while (true) {
//        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
//        strcpy(&formatted[0], fmt_str.c_str());
//                va_start(ap, fmt_str);
//        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
//                va_end(ap);
//        if (final_n < 0 || final_n >= n)
//            n += abs(final_n - n + 1);
//        else
//            break;
//    }
//    return std::string(formatted.get());
//
//
//}

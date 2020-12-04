//
// Created by xhy on 2020/8/25.
//

#include "Message.h"
#include <cstdarg>
#include "DirtyLogger.h"

using namespace SymHook;

void mcbe_sendMessage(std::string &s, Actor *player) {
    if (!player) {
        L_DEBUG("send message [%s] to a nullptr player", s.c_str());
        return;
    }
    L_DEBUG("send message [%s] to %s", player->getNameTag().c_str());
    std::vector<std::string> v;
    v.emplace_back("test");
    SYM_CALL(
            void(*)(bool, Actor *, std::string &, std::vector<std::string> &),
            MSSYM_MD5_24be62e9330073695808606844de0d99,
            true, player, s, v);
}


std::string gbkToUtf8(const char *src_str) {
    int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, nullptr, 0);
    auto *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, nullptr, nullptr);
    std::string strTemp(str);
    delete[] wstr;
    delete[] str;
    return strTemp;
}



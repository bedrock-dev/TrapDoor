//
// Created by xhy on 2020/8/28.
//
//#include "tools/MessageBuilder.h"
#include <iostream>
#include "tools/dbg.h"
#include <string>
#include <fstream>
#include "tools/DirtyLogger.h"
#include "common/ConfigManager.h"

using json = nlohmann::json;

int main() {
    char *str = new char[12];
    for (int i = 0; i < 12; ++i) {
        str[i] = 'a';
    }
    str[11] = 0;
    std::string s(str);
    delete [] str;
    std::cout<<s;
    return 0;
}

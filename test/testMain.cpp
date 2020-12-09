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

    std::map<int, int> m;
    auto a =  m.operator[](1);
    m[1] = 2;
    std::cout << a<<std::endl;
    std::cout<<m.size();
    return 0;
}




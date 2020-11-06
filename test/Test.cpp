//
// Created by xhy on 2020/8/28.
//
//#include "tools/MessageBuilder.h"
#include <iostream>
#include "tools/dbg.h"
#include <string>

int main() {
    std::string s = "QAQ";
    auto b = "ccc" + s;
    std::cout<<b;
    return 0;
}

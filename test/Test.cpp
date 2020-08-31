//
// Created by xhy on 2020/8/28.
//
#include "tools/MessageBuilder.h"
#include <iostream>
#include "tools/dbg.h"
int main() {
    std::string s = "name: minecraft:lapis_block";
     std::cout<<s.erase(0,6);
    return 0;
}



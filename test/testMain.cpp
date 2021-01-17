//
// Created by xhy on 2020/8/28.
//
//#include "tools/MessageBuilder.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdarg>
#include <cstdio>


int main() {

    std::string s = "AAAA";
    std::string s2 = "player";
    int a = 1;
    printf("%-20s %d\n", s.c_str(), a);
    printf("%-20s %d\n", s2.c_str(), a);
    return 0;
}



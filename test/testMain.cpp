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
    initLogger("QAQ", true);
    ConfigManager manager;
    manager.initialize("config.json");
    return 0;
}

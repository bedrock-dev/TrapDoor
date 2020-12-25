//
// Created by xhy on 2020/8/28.
//
//#include "tools/MessageBuilder.h"
#include <iostream>
#include <string>
#include <fstream>
#include "tools/DirtyLogger.h"
#include "common/ConfigManager.h"

using json = nlohmann::json;

int main() {
    initLogger("trapdoor.log", true);
    ConfigManager configManager;
    configManager.initialize("config.json");
    // graphics::drawLine({12,3,12},FACING::NEG_X,5,graphics::COLOR::WHITE);
    return 0;
}



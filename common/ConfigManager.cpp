//
// Created by xhy on 2020/11/25.
//

#include "ConfigManager.h"
#include "tools/DirtyLogger.h"

bool ConfigManager::initialize(const std::string &configFIleName) {
    if (!this->read(configFIleName))return false;
    //是否是开发者模式
    auto developModeObj = configJson["develop_mode"];
    L_INFO("set log level to debug: %d", developModeObj.is_boolean());
    if (developModeObj.is_boolean() && developModeObj.get<bool>()) {
        setLogLevel(LOG_LEVEL::LOG_DEBUG);
    } else {
        L_WARNING("develop_mode config is invalid");
    }
    L_INFO("read commands");
//    //命令是否启用
//    auto commandsObj = configJson["commands"];
//    for (auto commandObj:commandsObj) {
//    }
}


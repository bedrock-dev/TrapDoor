//
// Created by xhy on 2020/11/25.
//

#ifndef TRAPDOOR_CONFIGMANAGER_H
#define TRAPDOOR_CONFIGMANAGER_H

#include "tools/json.hpp"
#include <fstream>
#include "tools/DirtyLogger.h"
#include <map>

using json = nlohmann::json;

struct CommandConfig {
    bool enable;
    int permissionLevel;
};


class ConfigManager {
private:
    json configJson;
    std::map<std::string, CommandConfig> commandList;
    std::map<std::string, bool> functionList;
    std::map<std::string, std::string> parricleNameList;
    size_t particleShowFrequency = 1;

public:

    bool initialize(const std::string &configFIleName);

    bool read(const std::string &configFileName) {
        try {
            std::fstream f(configFileName);
            f << configJson;
            L_INFO("read config file %s successfully", configFileName.c_str());
            return true;
        } catch (std::exception &e) {
            L_ERROR("can not read config file %s ", configFileName.c_str());
            return false;
        }

    }
};

#endif //TRAPDOOR_CONFIGMANAGER_H

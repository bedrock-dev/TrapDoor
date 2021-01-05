//
// Created by xhy on 2020/11/25.
//

#include "ConfigManager.h"
#include "tools/DirtyLogger.h"
#include "commands/CommandManager.h"
#include <iostream>

namespace mod {


    bool ConfigManager::initialize(const std::string &configFIleName) {
        L_INFO("config manager developing");
        if (!this->readConfigFile(configFIleName))return false;
        if (!this->readCommandConfig())return false;
//        if (!this->readFunctionConfig())return false;
//        if (!this->readParticleConfig())return false;
        return true;
    }

    bool ConfigManager::readCommandConfig() {
        auto commandConfigs = this->configJson["commands"];
        trapdoor::CommandConfig tempConfig;
        try {
            for (const auto &i :commandConfigs.items()) {
                const auto &value = i.value();
                tempConfig.enable = value["enable"].get<bool>();
                tempConfig.permissionLevel = static_cast<trapdoor::CommandPermissionLevel>(value["permissionLevel"].get<int>());
                tempConfig.survival = value["survival"].get<bool>();
                tempConfig.needCheat = value["needCheat"].get<bool>();
                this->commandsConfig.insert({i.key(), tempConfig});
            }
        } catch (const std::exception &e) {
            L_ERROR("%s", e.what());
            return false;
        }
        return true;
    }

    const ConfigManager::FunctionConfig &ConfigManager::getFunctionConfig() {
        return this->functionConfig;
    }

    std::map<std::string, trapdoor::CommandConfig> &ConfigManager::getCommandsConfig() {
        return this->commandsConfig;
    }

    bool ConfigManager::readConfigFile(const std::string &configFileName) {
        try {
            std::ifstream i(configFileName);
            i >> this->configJson;
            L_INFO("read config file %s successfully", configFileName.c_str());
            return true;
        } catch (std::exception &e) {
            L_ERROR("can not read config file %s ", configFileName.c_str());
            return false;
        }
    }


    bool ConfigManager::readFunctionConfig() {
        try {
            auto funcConfig = this->configJson["function"];
            this->functionConfig.cactusRotation = funcConfig["cactusRotation"].get<bool>();
            this->functionConfig.explosion = funcConfig["explosion"].get<bool>();
            this->functionConfig.hopperCounter = funcConfig["hopperCounter"].get<bool>();
            this->functionConfig.playerSelection = funcConfig["playerSelection"].get<bool>();
            this->functionConfig.redstoneStick = funcConfig["redstoneStick"].get<bool>();
            this->functionConfig.lowerCommandLevel = funcConfig["lowerCommandLevel"].get<bool>();
        } catch (std::exception &e) {
            L_ERROR("%s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readParticleConfig() {
        try {
            auto partConfig = this->configJson["particle"];
            auto particleShowFrequency = partConfig["frequency"].get<size_t>();
            this->particleConfig.frequency = particleShowFrequency;
            if (particleShowFrequency <= 0) {
                L_WARNING("invalid frequency value,set to default 40");
                this->particleConfig.frequency = 40;
            }
            auto pvd = partConfig["defaultViewDistance"].get<size_t>();
            this->particleConfig.defaultViewDistance = pvd;
            if (pvd <= 0) {
                L_WARNING("invalid pvd value,set to default 128");
                this->particleConfig.frequency = 128;
            }
            this->particleConfig.performanceMode = partConfig["performanceMode"].get<bool>();
        } catch (std::exception &e) {
            L_ERROR("%s", e.what());
            return false;
        }
        return true;

    }


    void ConfigManager::printAllConfig() const {

    }

    const ConfigManager::ParticleConfig &ConfigManager::getParticleConfig() {
        return this->particleConfig;
    }

}
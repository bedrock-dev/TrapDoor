//
// Created by xhy on 2020/11/25.
//

#include "ConfigManager.h"
#include "tools/DirtyLogger.h"
#include "commands/CommandManager.h"
#include "graphics/Particle.h"
#include "graphics/Graphics.h"

#include <iostream>

namespace mod {
    namespace {


        trapdoor::GRAPHIC_COLOR str2color(std::string &color) {
            if (color == "red") {
                return GRAPH_COLOR::RED;
            } else if (color == "green") {
                return GRAPH_COLOR::GREEN;
            } else if (color == "yellow") {
                return GRAPH_COLOR::YELLOW;
            } else if (color == "blue") {
                return GRAPH_COLOR::BLUE;
            }
            return GRAPH_COLOR::WHITE;
        }
    }

    bool ConfigManager::initialize(const std::string &configFileName) {
        L_INFO("init config");
        if (!this->readConfigFile(configFileName))return false;
        if (!this->readCommandConfig())return false;
        if (!this->readLowLevelVanillaCommands())return false;
        if (!this->readServerConfig())return false;
        if (!this->readVillageConfig())return false;
//        if (!this->readFunctionConfig())return false;
//        if (!this->readParticleConfig())return false;
        this->printAllConfig();
        return true;
    }

    bool ConfigManager::readCommandConfig() {
        L_INFO("begin read command permission info");
        auto commandConfigs = this->configJson["commands"];
        trapdoor::CommandConfig tempConfig;
        try {
            for (const auto &i :commandConfigs.items()) {
                const auto &value = i.value();
                tempConfig.enable = value["enable"].get<bool>();
                tempConfig.permissionLevel = static_cast<trapdoor::CommandPermissionLevel>(value["permissionLevel"].get<int>());
                //关闭了生存模式和作弊检查
                //  tempConfig.survival = value["survival"].get<bool>();
                // tempConfig.needCheat = value["needCheat"].get<bool>();
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
        L_INFO("here are the all low level commands:");
        for (const auto &item:this->lowerLevelVanillaCommands) {
            L_INFO("%s", item.c_str());
        }
    }

    const ConfigManager::ParticleConfig &ConfigManager::getParticleConfig() {
        return this->particleConfig;
    }

    bool ConfigManager::readLowLevelVanillaCommands() {
        L_INFO("begin read low level vanilla command info");
        try {
            auto lowLevelVanillaCommandsConfig = this->configJson["lowLevelVanillaCommands"];
            for (const auto &i:lowLevelVanillaCommandsConfig) {
                this->lowerLevelVanillaCommands.insert(i.get<std::string>());
            }
        } catch (std::exception &e) {
            L_ERROR("%s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readServerConfig() {
        L_INFO("begin read server  info");
        try {
            auto config = this->configJson["server"];
            //以后可能会有其它配置项
            this->serverConfig.levelName = config["levelName"].get<std::string>();
            L_INFO("read level name  as :%s", serverConfig.levelName.c_str());
        } catch (std::exception &e) {
            L_ERROR("%s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readVillageConfig() {
        L_INFO("begin read village config info");
        try {
            auto config = this->configJson["village"];
            //以后可能会有其它配置项
            auto boundColor = config["bound"].get<std::string>();
            auto spawnColor = config["spawn"].get<std::string>();
            auto poiQuery = config["poiQuery"].get<std::string>();
            auto centerParticle = config["center"].get<std::string>();
            this->villageHelperConfig = {
                    str2color(boundColor),
                    str2color(spawnColor),
                    str2color(poiQuery),
                    centerParticle
            };
            L_INFO("bound color: %s, spawn color: %s, poiQueryColor: %s,center:%s",
                   boundColor.c_str(),
                   spawnColor.c_str(),
                   poiQuery.c_str(),
                   centerParticle.c_str()
            );
        } catch (std::exception &e) {
            L_ERROR("%s", e.what());
            return false;
        }
        return true;
    }

}
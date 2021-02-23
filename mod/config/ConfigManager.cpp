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
        L_DEBUG("begin read config file %s", configFileName.c_str());
        if (!this->readConfigFile(configFileName))return false;
        if (!this->readEULA())return false;
        if (!this->readCommandConfig())return false;
        if (!this->readLowLevelVanillaCommands())return false;
        if (!this->readServerConfig())return false;
        if (!this->readVillageConfig())return false;
        if (!this->readFunctionConfig())return false;
        if (!this->readSelfConfig())return false;
        this->printAllConfig();
        return true;
    }

    bool ConfigManager::readCommandConfig() {
        L_DEBUG("begin read command permission info");
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

            for (const auto &item:this->commandsConfig) {
                L_DEBUG(" - %-10s enable:%d  level:%d", item.first.c_str(),
                        item.second.enable,
                        item.second.permissionLevel
                );
            }
            L_DEBUG("read command permission info successfully\n");
        } catch (const std::exception &e) {
            L_ERROR("error read command config : %s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readConfigFile(const std::string &configFileName) {
        try {
            std::ifstream i(configFileName);
            i >> this->configJson;
            L_DEBUG("read config file %s successfully\n", configFileName.c_str());
            return true;
        } catch (std::exception &e) {
            L_ERROR("can not read config file %s ", configFileName.c_str());
            return false;
        }
    }


    bool ConfigManager::readFunctionConfig() {
        L_DEBUG("begin read function config");
        try {
            auto funcConfig = this->configJson["functionsEnable"];
            this->functionConfig.hopperCounter = funcConfig["hopperCounter"].get<bool>();
            //    this->functionConfig.explosion = funcConfig["explosion"].get<bool>();
            this->functionConfig.spawnHelper = funcConfig["spawnHelper"].get<bool>();
            this->functionConfig.cactusRotation = funcConfig["cactusRotate"].get<bool>();
            this->functionConfig.simpleDraw = funcConfig["simpleDraw"].get<bool>();
            this->functionConfig.playerStat = funcConfig["playerStat"].get<bool>();

            L_DEBUG("read function config successfully\n");
        } catch (std::exception &e) {
            L_ERROR("can not read function config： %s", e.what());
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


    bool ConfigManager::readLowLevelVanillaCommands() {
        L_DEBUG("begin read low level vanilla command info");
        try {
            auto lowLevelVanillaCommandsConfig = this->configJson["lowLevelVanillaCommands"];
            for (const auto &i:lowLevelVanillaCommandsConfig) {
                this->lowerLevelVanillaCommands.insert(i.get<std::string>());
            }
            L_DEBUG("here are the all low level commands:");
            for (const auto &item:this->lowerLevelVanillaCommands) {
                L_DEBUG("- %s", item.c_str());
            }
            L_DEBUG("read low level vanilla commands successfully\n");
        } catch (std::exception &e) {
            L_ERROR("error read low level vanilla command info : %s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readServerConfig() {
        L_DEBUG("begin read server info");
        try {
            auto config = this->configJson["server"];
            //以后可能会有其它配置项
            this->serverConfig.levelName = config["levelName"].get<std::string>();
            L_DEBUG(" - levelMame : %s\nread server info successfully\n", serverConfig.levelName.c_str());
        } catch (std::exception &e) {
            L_ERROR("can not read server config : %s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readVillageConfig() {
        L_DEBUG("begin read village config info");
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
            L_DEBUG(" - bound color: %s\n - spawn color: %s\n - poiQueryColor: %s\n - center:%s",
                    boundColor.c_str(),
                    spawnColor.c_str(),
                    poiQuery.c_str(),
                    centerParticle.c_str()
            );
            L_DEBUG("read village color successfully\n");
        } catch (std::exception &e) {
            L_ERROR("can not read village config : %s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readSelfConfig() {
        L_DEBUG("begin read self command config");
        try {
            auto funcConfig = this->configJson["selfEnable"];
            this->selfEnableConfig.enableChunkShow = funcConfig["chunkShow"].get<bool>();
            this->selfEnableConfig.enableDistanceMeasure = funcConfig["distanceMeasure"].get<bool>();
            this->selfEnableConfig.enableRedstoneStick = funcConfig["redstoneStick"].get<bool>();
            L_DEBUG("read self command config successfully\n");
        } catch (std::exception &e) {
            L_ERROR("can not read self config: %s", e.what());
            return false;
        }
        return true;
    }

    bool ConfigManager::readEULA() {
        L_DEBUG("begin read EULA");
        try {
            auto config = this->configJson["EULA"];
            //以后可能会有其它配置项
            auto acceptEULA = config.get<bool>();
            if (!acceptEULA) {
                L_ERROR("you need to accept the EULA before use trapdoor mod");
            } else {
                L_DEBUG("read eula success");
            }
            return acceptEULA;
        } catch (std::exception &e) {
            L_ERROR("can not read server config : %s", e.what());
            return false;
        }
        return true;
    }

}
//
// Created by xhy on 2020/11/25.
//

#ifndef TRAPDOOR_CONFIGMANAGER_H
#define TRAPDOOR_CONFIGMANAGER_H

#include "tools/json.hpp"
#include <fstream>
#include "tools/DirtyLogger.h"
#include "commands/CommandManager.h"
#include "tools/noncopyable .h"
#include <map>
#include <set>
#include "Village.h"

namespace mod {
    using json = nlohmann::json;

    class ConfigManager : public noncopyable {
    public:
        //命令配置选项

        struct FunctionConfig {
            bool hopperCounter = true;
            bool explosion = true;
            bool cactusRotation = false;
            bool playerSelection = false;
            bool redstoneStick = true;
            bool lowerCommandLevel = false;
        };

        struct ParticleConfig {
            size_t frequency = 40; //显示频率(gt)
            size_t defaultViewDistance = 128;//blockpos
            bool performanceMode = false;
        };

        struct ServerConfig {
            std::string levelName;
        };
    private:

        json configJson;
        std::map<std::string, trapdoor::CommandConfig> commandsConfig;
        std::set<std::string> lowerLevelVanillaCommands;

        FunctionConfig functionConfig;
        ParticleConfig particleConfig;
        VillageHelperConfig villageHelperConfig;
        ServerConfig serverConfig;

        bool readCommandConfig();

        bool readConfigFile(const std::string &configFileName);

        bool readFunctionConfig();

        bool readParticleConfig();

        bool readLowLevelVanillaCommands();

        bool readServerConfig();

        bool readVillageConfig();

    public:

        const FunctionConfig &getFunctionConfig();

        std::map<std::string, trapdoor::CommandConfig> &getCommandsConfig();

        const ParticleConfig &getParticleConfig();

        bool initialize(const std::string &configFileName);

        void printAllConfig() const;

        inline const std::set<std::string> &getLowLevelCommands() const { return this->lowerLevelVanillaCommands; }

        inline const VillageHelperConfig &getVillageConfig() const { return this->villageHelperConfig; }

        inline const ServerConfig &getServerConfig() const { return this->serverConfig; }

    };
}

#endif //TRAPDOOR_CONFIGMANAGER_H

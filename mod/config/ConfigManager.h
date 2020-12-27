//
// Created by xhy on 2020/11/25.
//

#ifndef TRAPDOOR_CONFIGMANAGER_H
#define TRAPDOOR_CONFIGMANAGER_H

#include "tools/json.hpp"
#include <fstream>
#include "tools/DirtyLogger.h"
#include <map>



/*
 * todo
 * 开发中，请无视
 *
 *
 */
namespace mod {
    using json = nlohmann::json;

    class ConfigManager {
    public:
        //命令配置选项
        struct CommandConfig {
            bool enable = true; //是否启用
            int permissionLevel = 2; //权限等级
            bool survival = false; //生存中是否可用
        };
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

    private:

        json configJson;
        std::map<std::string, CommandConfig> commandsConfig;
        FunctionConfig functionConfig;
        ParticleConfig particleConfig;

        bool readCommandConfig();

        bool readConfigFile(const std::string &configFileName);

        bool readFunctionConfig();

        bool readParticleConfig();

    public:

        const FunctionConfig &getFunctionConfig();

        const std::map<std::string, CommandConfig> &getCommandsConfig();

        const ParticleConfig &getParticleConfig();


        bool initialize(const std::string &configFIleName);

        void printAllConfig() const;

    };
}

#endif //TRAPDOOR_CONFIGMANAGER_H
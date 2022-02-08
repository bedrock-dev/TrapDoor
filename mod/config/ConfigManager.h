//
// Created by xhy on 2020/11/25.
//

#ifndef TRAPDOOR_CONFIGMANAGER_H
#define TRAPDOOR_CONFIGMANAGER_H

#include <fstream>
#include <map>
#include <set>

#include "Village.h"
#include "commands/CommandManager.h"
#include "tools/DirtyLogger.h"
#include "tools/json.hpp"
#include "tools/noncopyable .h"

namespace mod {
    using json = nlohmann::json;

    class ConfigManager : public noncopyable {
       public:
        //命令配置选项结构体
        struct FunctionEnableConfig {
            bool hopperCounter = true;    //漏斗计数器
            bool explosion = true;        //爆炸破坏地形
            bool spawnHelper = false;     //刷怪指示器
            bool cactusRotation = false;  //仙人掌转方块
            bool playerStat = false;      //玩家行为统计
            bool simpleDraw = false;      //画圆
        };

        struct SelfEnableConfig {
            bool enableChunkShow = true;        //区块显示
            bool enableDistanceMeasure = true;  //距离测量
            bool enableRedstoneStick = true;    //信号源提示
        };

        struct ParticleConfig {
            size_t frequency = 40;             //显示频率(gt)
            size_t defaultViewDistance = 128;  // blockpos
            bool performanceMode = false;
        };

        struct ServerConfig {
            std::string levelName;
            std::string wsUrl;
        };

       private:
        json configJson;
        std::map<std::string, trapdoor::CommandConfig> commandsConfig;
        std::set<std::string> lowerLevelVanillaCommands;

        FunctionEnableConfig functionConfig;
        ParticleConfig particleConfig;
        VillageHelperConfig villageHelperConfig;
        ServerConfig serverConfig;
        SelfEnableConfig selfEnableConfig;

        bool readCommandConfig();

        bool readConfigFile(const std::string &configFileName);

        bool readFunctionConfig();

        bool readSelfConfig();

        bool readParticleConfig();

        bool readDevOption();

        bool readLowLevelVanillaCommands();

        bool readServerConfig();

        bool readVillageConfig();

       public:
        inline const FunctionEnableConfig &getFunctionConfig() {
            return this->functionConfig;
        }

        inline std::map<std::string, trapdoor::CommandConfig>
            &getCommandsConfig() {
            return this->commandsConfig;
        }

        inline const ParticleConfig &getParticleConfig() {
            return this->particleConfig;
        }

        bool initialize(const std::string &configFileName);

        void printAllConfig() const;

        inline const std::set<std::string> &getLowLevelCommands() const {
            return this->lowerLevelVanillaCommands;
        }

        inline const VillageHelperConfig &getVillageConfig() const {
            return this->villageHelperConfig;
        }

        inline const ServerConfig &getServerConfig() const {
            return this->serverConfig;
        }

        inline const SelfEnableConfig &getSelfEnableConfig() const {
            return this->selfEnableConfig;
        }
    };
}  // namespace mod

#endif  // TRAPDOOR_CONFIGMANAGER_H

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
        //命令配置选项结构体
        struct FunctionEnableConfig {
            bool hopperCounter = true; //漏斗计数器
            bool explosion = true;  //爆炸破坏地形
            bool spawnHelper = true; //刷怪指示器
            bool cactusRotation = false; //仙人掌转方块
            bool playerStat = false; //玩家行为统计
            bool simpleDraw = true; //画圆(和球)
        };

        struct SelfEnableConfig {
            bool enableChunkShow = true;   //区块显示
            bool enableDistanceMeasure = true; //距离测量
            bool enableRedstoneStick = true; //信号源提示
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

        FunctionEnableConfig functionConfig;
        ParticleConfig particleConfig;
        VillageHelperConfig villageHelperConfig;
        ServerConfig serverConfig;
        SelfEnableConfig selfEnableConfig;

        //读取配置文件
        bool readConfigFile(const std::string &configFileName);

        //读取命令配置信息
        bool readCommandConfig();

        //读取函数赔偿信息
        bool readFunctionConfig();

        bool readSelfConfig();

        //读取EULA
        bool readEULA();

        //读取指令列表
        bool readLowLevelVanillaCommands();

        //读取服务器信息
        bool readServerConfig();

        //读取村庄配置信息
        bool readVillageConfig();

    public:

        inline const FunctionEnableConfig &getFunctionConfig() { return this->functionConfig; }

        inline std::map<std::string, trapdoor::CommandConfig> &getCommandsConfig() { return this->commandsConfig; }

        bool initialize(const std::string &configFileName);

        inline const std::set<std::string> &getLowLevelCommands() const { return this->lowerLevelVanillaCommands; }

        inline const VillageHelperConfig &getVillageConfig() const { return this->villageHelperConfig; }

        inline const ServerConfig &getServerConfig() const { return this->serverConfig; }

        inline const SelfEnableConfig &getSelfEnableConfig() const { return this->selfEnableConfig; }
    };
}

#endif //TRAPDOOR_CONFIGMANAGER_H

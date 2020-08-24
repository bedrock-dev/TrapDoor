#pragma warning (disable:4819)
//
// Created by xhy on 2020/8/24.
//
#include "Shell.h"

std::map<std::string, CmdType> commandMap = {  // NOLINT(cert-err58-cpp)
        {"./tick",  CmdType::Tick},
        {"fw",      ParaType::TickForward},
        {"slow",    ParaType::TickSlow},
        {"fz",      ParaType::TickFreeze},
        {"r",       ParaType::TickReset},
        {"./prof",  CmdType::Profile},
        {"./vill",  CmdType::Village},
        {"./func",  CmdType::Function},
        {"./p",     CmdType::Position},
        {"./spawn", CmdType::Spawn},
        {"./help",  CmdType::Help},
        {"./conf",  CmdType::Config}
};


std::vector<std::string> tokenize(std::string &commandString) {
    std::vector<std::string> tokens;
    std::stringstream s(commandString);
    std::string command;
    while (s >> commandString)
        tokens.push_back(commandString);
    return tokens;
}

THook(void, MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334, void *self, std::string const &playerName,
      std::string &commandLine) {
    if (commandLine.size() < 2)return;
    if (!(commandLine[0] == '.' && commandLine[1] == '/'))return;
    auto tokens = tokenize(commandLine);
    auto result = commandMap.find(tokens[0]);
    if (result == commandMap.end()) {
        error("unknown command , use [./help] to show help");
        return;
    }

    const char *banner = "§5§l          TRAPDOOR v0.1.4                \n";
    switch (result->second) {
        case CmdType::Tick:
            if (tokens.size() == 1)return;
            if (tokens[1] == "fz" || tokens[1] == "frozen") {//重置为正常状态
                tick::freezeWorld();
            } else if (tokens[1] == "reset" || tokens[1] == "r") {
                tick::resetWorld();
            } else if (tokens[1] == "forward" || tokens[1] == "fw") {//前进n tick
                if (tokens.size() != 3)return;
                int time = strtol(tokens[2].c_str(), nullptr, 10);
                if (time < 0) {
                    error("invalid parameter\n");
                    return;
                }
                tick::forwardWorld(time);
            } else if (tokens[1] == "slow") {
                if (tokens.size() != 3)return;
                int time = strtol(tokens[2].c_str(), nullptr, 10);
                if (time < 0) {
                    error("invalid parameter\n");
                    return;
                }
                tick::slowWorld(time);
            }
            break;
            //Profile
        case CmdType::Profile:
            tick::profileWorld();
            break;

        case CmdType::Village:
            if (tokens.size() == 1)return;
            if (tokens[1] == "draw") {
                if (tokens.size() == 3) {
                    if (tokens[2] == "true") {
                        enableVillageShow = true;
                    } else if (tokens[2] == "false") {
                        enableVillageShow = false;
                    }
                    return;
                } else {
                    gamePrintf("use ./vill draw [true/false]");
                }
            } else if (tokens[1] == "list") {
                village::listVillages();
            }
            break;

        case CmdType::Function:
            if (tokens.size() != 3 || !(tokens[2] == "true" || tokens[2] == "false")) {
                error("use ./func xxx [true/false]\nfor more info type /help");
                return;
            }
            if (tokens[1] == "extratickwork") {
                enableExtraTickWork = tokens[2] == "true";
            } else if (tokens[1] == "explosion") {
                enableExplosion = tokens[2] == "true";
            }
            break;

        case CmdType::Position:
            enableMarkPos = !enableMarkPos;
            break;
        case CmdType::Config:
            if (tokens.size() == 3) {
                if (tokens[1] == "particleViewDis" || tokens[1] == "pvd") {
                    int distance = strtol(tokens[2].c_str(), nullptr, 10);
                    if (distance > 0 && distance < 32768) {
                        particleViewDistance = distance;
                        gamePrintf("particle view set to %d", distance);
                    } else {
                        error("invalid distance");
                    }
                }
            } else {
                error("unknown command");
            }
            break;

        case CmdType::Help:
            gamePrintf("%s" \
                    "§r§6./tick fz - freeze the world\n"\
                    "./tick slow [num] -  slow the world\n"\
                    "./tick fw [num] - forward the world to num tick\n"\
                    "./vill draw [true/false] - (dis)enable the village bound and center show\n"\
                    "./vill list - list all the ticking villages\n"\
                    "./func explosion [true/false] - (dis)enable explosion\n"\
                    "./prof - profile the world run\n"\
                    "./p - line measure(need rewrite)\n"\
                    "./spawn start -  start the mob spawner counter\n"\
                    "./spawn end -  end the mob spawner counter\n"\
                    "./spawn p -  print the counter result\n"\
                    "./spawn info -  print some mob info\n"\
                    "./conf pvd [distance] - config the particle view distance(default=128)\n-------------------\n",
                       banner);
            //gamePrintf("§rThanks:\commandMap zhkj-liuxiaohua ΘΣΦΓΥΔΝ 莵道三室戸 兰瑟头颅emm想无 TestBH 暮月云龙 其它相关SAC群友");
            break;

        case CmdType::Spawn :
            if (tokens.size() == 1)return;
            if (tokens[1] == "start") {
                spawn::startSpawnCounter();
            } else if (tokens[1] == "end") {
                spawn::endSpawnerCounter();
            } else if (tokens[1] == "p" || tokens[1] == "print") {
                auto str = tokens.size() == 3 ? tokens[2] : "null";
                spawn::spawnAnalysis(str);
            } else if (tokens[1] == "info") {
                spawn::sendMobInfo();
            }
        default:
            break;
    }
    return original(self, playerName, commandLine);
}




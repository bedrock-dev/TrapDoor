#pragma once

#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include "Tick.h"
#include "Village.h"
#include <map>
#include "Actor.h"
#include "Spawn.h"
#include <vector>

using namespace SymHook;
enum class CmdType {
    Tick,
    Profile,
    Village,
    Function,
    Position,
    Info,
    Help,
    Spawn
};

std::map<std::string, CmdType> cmdMap = {
        {"./tick",  CmdType::Tick},
        {"./prof",  CmdType::Profile},
        {"./vill",  CmdType::Village},
        {"./func",  CmdType::Function},
        {"./p",     CmdType::Position},
        {"./spawn", CmdType::Spawn},
        {"./info",  CmdType::Info},
        {"./help",  CmdType::Help}
};


THook(void, MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334, void *self, std::string const &playerName,
      std::string &commandLine) {
    if (commandLine.size() < 2)return;
    if (!(commandLine[0] == '.' && commandLine[1] == '/'))return;
    std::vector<std::string> tokens;
    std::stringstream s(commandLine);
    std::string command;
    while (s >> commandLine)
        tokens.push_back(commandLine);
    auto result = cmdMap.find(tokens[0]);
    if (result == cmdMap.end()) {
        error("unknown command , use [./help] to show help");
        return;
    }


    const char *banner = "§6          _                \n"
                         "_|_ __ _ |_) _| _  _  __   \n"
                         " |_ | (_||  (_|(_)(_) |   ";

    switch (result->second) {
        case CmdType::Tick:
            if (tokens.size() == 1)return;
            //暂停世界运行
            if (tokens[1] == "fz" || tokens[1] == "frozen") {//重置为正常状态
                worldFrozen();
            } else if (tokens[1] == "reset" || tokens[1] == "r") {
                worldReset();
            } else if (tokens[1] == "forward" || tokens[1] == "fw") {//前进n tick
                if (tokens.size() != 3)return;
                int time = strtol(tokens[2].c_str(), nullptr, 10);
                if (time < 0) {
                    error("invalid parameter\n");
                    return;
                }
                worldForward(time);
            }

                //放慢
            else if (tokens[1] == "slow") {
                if (tokens.size() != 3)return;
                int time = strtol(tokens[2].c_str(), nullptr, 10);
                if (time < 0) {
                    error("invalid parameter\n");
                    return;
                }
                worldSlow(time);
            }
            break;

        case CmdType::Profile:
            worldProfile();
            break;

        case CmdType::Village:
            if (tokens.size() == 1)return;
            if (tokens[1] == "draw") {//重置为正常状态
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
                listVillages();
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
        case CmdType::Info:
            sendInfo();
            break;
        case CmdType::Help:
            gamePrintf("%s" \
                    "./tick fz freeze the world\n"\
                    "./tick slow [num] slow the world\n"\
                    "./tick fw [num] forward the world to num tick\n"\
                    "./vill draw [true/false] (dis)enable the village bound and center show\n"\
                    "./vill list  list all the ticking villages\n"\
                    "./func explosion [true/false] (dis)enable explosion\n"\
                    "./prof profile the world run\n"\
                    "./p line measure\n", banner);
            break;
        case CmdType::Spawn :
            if (tokens.size() == 1)return;
            if (tokens[1] == "start") {
                startSpawnCounter();
            } else if (tokens[1] == "end") {
                endSpawnerCounter();
            } else if (tokens[1] == "clear") {
                clearSpawnCounter();
            } else if (tokens[1] == "p" || tokens[1] == "print") {
                auto str = tokens.size() == 3 ? tokens[2] : "null";
                spawnAnalysis(str);
            }
        default:
            break;
    }
    return original(self, playerName, commandLine);
}



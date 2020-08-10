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
	Help
};

std::map<std::string, CmdType> cmd_map = {
		{"./tick", CmdType::Tick},
		{"./prof", CmdType::Profile},
		{"./vill",CmdType::Village},
		{"./func",CmdType::Function},
		{"./p",CmdType::Position},
		{"./info",CmdType::Info},
		{"./help",CmdType::Help}
};




THook(void, MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334, void* self, std::string const& player_name, std::string& command_line) {
	if (command_line.size() < 2)return;
	if (!(command_line[0] == '.' && command_line[1] == '/'))return;
	std::vector<std::string> tokens;
	std::stringstream s(command_line);
	std::string command;
	while (s >> command_line)
		tokens.push_back(command_line);
	auto result = cmd_map.find(tokens[0]);
	if (result == cmd_map.end()) {
		printf("unknown command\n");
		return;
	}
	switch (result->second) {
	case CmdType::Tick:
		if (tokens.size() == 1)return;

		//暂停世界运行
		if (tokens[1] == "fz" || tokens[1] == "frozen") {//重置为正常状态
			worldFrozen();
		}
		else if (tokens[1] == "reset" || tokens[1] == "r") {
			worldReset();
		}
		else if (tokens[1] == "forward" || tokens[1] == "fw") {//前进n tick
			if (tokens.size() != 3)return;
			int time = strtol(tokens[2].c_str(), nullptr, 10);
			if (time < 0) {
				sendText("invalid parameter\n");
				return;
			}
			worldForword(time);
		}


		//放慢
		else if (tokens[1] == "slow") {
			if (tokens.size() != 3)return;
			int time = strtol(tokens[2].c_str(), nullptr, 10);
			if (time < 0) {
				sendText("invalid parameter\n");
				return;
			}
			WorldSlow(time);
		}

		else if (tokens[1] == "step") {
			printf("step\n");
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
				}
				else if (tokens[2] == "false") {
					enableVillageShow = false;
				}
				return;
			}
			else
			{
				sendText("use ./vill draw [true/false]");
			}
		}
		else if (tokens[1] == "list") {
				listVillages();
		}
	
		break;

	case CmdType::Function:
		if (tokens.size() != 3 || !(tokens[2] == "true" || tokens[2] == "false")) {
			sendText("use ./func xxx [true/false]\nfor more info type /help");
			return;
		}
		if (tokens[1] == "extratickwork") 
		{
			enableExtraTickWork = tokens[2] == "true" ? true : false;
		}
		else if (tokens[1] == "explosion")
		{
			enableExplosion = tokens[2] == "true" ? true : false;
		}
	/*	else if (tokens[1] == "observe") {
			enableObserve = tokens[2] == "true" ? true : false;
			sendText("observe changed");
		}*/
		break;
	case CmdType::Position:
		enableMarkPos = !enableMarkPos;
		break;
	case CmdType::Info:
			sendInfo();
			break;
	default:
		break;
	}
	return original(self, player_name, command_line);
}



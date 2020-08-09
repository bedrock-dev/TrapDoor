#pragma once
#include "Cons.h"
#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include <vector>
using namespace SymHook;

/*获取实体调试信息*/
std::string getActorText(void* actor) {
	std::vector<std::string> info;
	SYM_CALL(void(*)(void*, std::vector<std::string>&),
		MSSYM_MD5_f04fad6bac034f1e861181d3580320f2,
		actor, info);
	std::string s;
	for (auto i : info) {
		s.append(i);
		s.append("\n");
	}
	return s;
}



/**实体标定**/
THook(
	void,
	MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z,
	void* p1,
	void* p2
) {
	if (p1 && p2) {
		printf("attack");
		auto text = getActorText(p2);
		msg(text);
	}
}

// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <Windows.h>
#include "tools/DirtyLogger.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"


void initConsole() {
    //support uft8
    system("chcp 65001");
    //enable colorful output
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //NOLINT
    SetConsoleMode(hOutput, dwMode);
}


trapdoor::BDSMod *createBDSModInstance() {
    return new mod::TrapdoorMod();
}

void mod_init() {
    initConsole();
    trapdoor::initLogger("trapdoor.log", false, true, true);
    mod::TrapdoorMod::printCopyRightInfo();
    auto *mod = createBDSModInstance();
    mod->asInstance<mod::TrapdoorMod>()->readConfigFile("trapdoor-config.json");
    trapdoor::initializeMod(mod);
}

void mod_exit() {}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
) {
    switch (ul_reason_for_call) {  //NOLINT
        case DLL_PROCESS_ATTACH:
            mod_init();
            break;
        case DLL_THREAD_ATTACH: //NOLINT
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            mod_exit();
            break;
    }
    return TRUE;
}

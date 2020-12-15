// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include  "lib/pch.h"
#include "lib/version.h"
#include "tools/DirtyLogger.h"
#include "common/Trapdoor.h"

#define DBG_MACRO_NO_WARNING

void mod_init() {

    system("chcp 65001");
    initLogger("trapdoor.log", false);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
    const char *banner =
            "\n"
            "  _______                  _                   \n"
            " |__   __|                | |                  \n"
            "    | |_ __ __ _ _ __   __| | ___   ___  _ __  \n"
            "    | | '__/ _` | '_ \\ / _` |/ _ \\ / _ \\| '__| \n"
            "    | | | | (_| | |_) | (_| | (_) | (_) | |    \n"
            "    |_|_|  \\__,_| .__/ \\__,_|\\___/ \\___/|_|    \n"
            "                | |                            \n"
            "                |_|                            ";
    printf(
            "%s\n%s  "
            "\ngithub:https://github.com/hhhxiao/MCBEtoolSet\nLicense: GPL\n",
            banner, trapDoorVersion);
    printf("build time: %s  %s\n", __DATE__, __TIME__);
}

void mod_exit() {}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            mod_init();
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            mod_exit();
            break;
    }
    return TRUE;
}


// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include  "lib/pch.h"
#define DBG_MACRO_NO_WARNING

void mod_init();

void mod_exit();

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


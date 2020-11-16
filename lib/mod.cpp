#include <cstdio>
#include "commands/Command.h"
#include "pch.h"
#include "version.h"

void mod_init() {
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
            banner, version);
    printf("build time: %s  %s\n", __DATE__, __TIME__);
}

void mod_exit() {}

#include <cstdio>

void mod_init() {
    const char *banner = "\n"
                         "  _______                  _                   \n"
                         " |__   __|                | |                  \n"
                         "    | |_ __ __ _ _ __   __| | ___   ___  _ __  \n"
                         "    | | '__/ _` | '_ \\ / _` |/ _ \\ / _ \\| '__| \n"
                         "    | | | | (_| | |_) | (_| | (_) | (_) | |    \n"
                         "    |_|_|  \\__,_| .__/ \\__,_|\\___/ \\___/|_|    \n"
                         "                | |                            \n"
                         "                |_|                            ";
    printf("%s\nTrapdoor V0.1.6-debug\ngithub:https://github.com/hhhxiao/MCBEtoolSet\nLicense: GPL\n", banner);
    printf("build time: %s  %s\n", __DATE__, __TIME__);
}

void mod_exit() {
}

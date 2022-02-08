

#include "FunctionCommands.h"

#include "commands/ArgHolder.h"
#include "commands/CommandNode.h"
#include "language/I18nManager.h"
#include "os/process_stat.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"

namespace mod {

    namespace {
        //[              |current usage      \ avaliable]
        bool buildBar(trapdoor::MessageBuilder& builder, int total,
                      int avaliable, int currentUsage, int length) {
            if (total == 0) {
                L_DEBUG("total = 0");
                builder.text("[  ")
                    .sText("Unknown", trapdoor::MSG_COLOR::RED)
                    .text("  ]");
                return false;
            }

            int len_1 = static_cast<int>(
                static_cast<float>(total - avaliable - currentUsage) / total *
                length);
            if (len_1 == 0) len_1++;

            int len_2 = static_cast<int>(static_cast<float>(currentUsage) /
                                         total * length);
            if (len_2 == 0) len_2++;
            int len_3 = length - len_1 - len_2;

            std::string s1(len_1, '|');
            std::string s2(len_2, '|');
            std::string s3(len_3, ' ');
            // builder.textF("[%s%s%s]", s1.c_str(), s2.c_str(), s3.c_str());
            builder.text("[");
            builder.sTextF(trapdoor::MSG_COLOR::GREEN, "%s", s2.c_str())
                .textF("%s", s1.c_str())
                .textF("%s]", s3.c_str());

            return true;
        }
    }  // namespace
    //便捷模式切换
    void registerGamemodeSwitchCommand(CommandManager& commandManager) {
        using namespace trapdoor;
        commandManager.registerCmd("o", "command.o.desc")->EXE({
            player->setGameMode(4);
            broadcastMsg(LANG("command.o.set"), player->getNameTag().c_str());
        });

        commandManager.registerCmd("s", "command.s.desc")->EXE({
            player->setGameMode(0);
            broadcastMsg(LANG("command.s.set"), player->getNameTag().c_str());
        });

        commandManager.registerCmd("c", "command.c.desc")->EXE({
            player->setGameMode(1);
            broadcastMsg(LANG("command.c.set"), player->getNameTag().c_str());
        });
    }

    void printfSysInfo(trapdoor::Actor* player) {
        // CPU
        // int currentProcessCPUUsage = getCurProcessCPUUsage();
        // int totalCPUUsage = static_cast<int>(GetCPULoad() * 100);
        // trapdoor::MessageBuilder builder;
        // builder.text("CPU  ");
        // buildBar(builder, 100, 100 - totalCPUUsage, currentProcessCPUUsage,
        // 50); builder.textF("  %d", currentProcessCPUUsage)
        //     .text("%%%%")
        //     .textF("  %d", totalCPUUsage)
        //     .text("%%%%\n");
        // builder.text("MEM  ");
        // // MEM
        // uint64_t memory = 0, virtualMemory = 0;
        // uint64_t total = 0, free = 0;
        // getCurProcessMemUsage(&memory, &virtualMemory);
        // getSystemMemorySize(&total, &free);
        // memory >>= 20u;
        // total >>= 20u;
        // free >>= 20u;
        // if (buildBar(builder, total, free, memory, 50)) {
        //     builder.textF("  %d MB %d MB\n", memory, total - free);
        // }
        // builder.send(player);
        int CPUUsage = getCurProcessCPUUsage();
        uint64_t memory, virtualMemory, ioRead, ioWrite;
        getCurProcessMemUsage(&memory, &virtualMemory);
        getIOBytes(&ioRead, &ioWrite);
        std::string stringBuilder;

        trapdoor::MessageBuilder builder;
        builder.text("CPU ")
            .sTextF(trapdoor::MSG_COLOR::GREEN, "%d", CPUUsage)
            .text("%%%%    ");
        builder.text("MEM ")
            .sTextF(trapdoor::MSG_COLOR::GREEN, "%d", memory >> 20u)
            .text("MB");
        builder.send(player);
        // stringBuilder += trapdoor::format(
        //     "CPU: %d %%%%\n"
        //     "Mem: " C_INT " MB VMem; " C_INT
        //     " MB\n"
        //     "Read/Write" C_INT "KB / " C_INT " KB",
        //     CPUUsage, memory >> 20u, virtualMemory >> 20u, ioRead >> 10u,
        //     ioWrite >> 10u);
        // trapdoor::info(player, stringBuilder);
    }
}  // namespace mod

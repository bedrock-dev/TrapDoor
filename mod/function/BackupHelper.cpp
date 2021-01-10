//
// Created by xhy on 2021/1/9.
//

#include "BackupHelper.h"
#include <string>
#include <cstdlib>
#include "BDSMod.h"
#include <chrono>
#include "tools/Message.h"
#include "tick/SimpleProfiler.h"
#include <filesystem>
#include <MsgBuilder.h>

namespace mod {

    namespace {
        bool isValidWorldFolder(const std::filesystem::path &path) {
            //check
            return true;
        }
    }

    void backup(trapdoor::Actor *player) {
        const std::string backupScript = R"(
        $Date =  Get-Date -UFormat "%m/%d/%Y %R"
        $SourcePath = "worlds/Bedrock level"
        $Destination = "Test2"
        Copy-Item -Path $SourcePath -Destination "$Destination\$date" -Recurse
    )";
        auto threadPool = trapdoor::bdsMod->getThreadPool();
        threadPool->enqueue([&]() {
            trapdoor::broadcastMsg("backup start");
            TIMER_START
            std::this_thread::sleep_for(std::chrono::seconds(5));
            TIMER_END
            auto cost = timeReslut / 1000000;
            // trapdoor::broadcastMsg("backup finish, %ds cost", static_cast<int>(cost));
        });
    }

    void initBackup() {
        std::filesystem::create_directory("trapdoor-backup");
    }

    void listAllBackups(trapdoor::Actor *player) {
        namespace fs = std::filesystem;
        fs::path backupRootPath("trapdoor-backup");
        if (!fs::exists(backupRootPath)) {
            trapdoor::error(player, "备份根目录不存在!");
            return;
        }
        trapdoor::MessageBuilder builder;
        int totalNum = 0, currentNum = 0;
        fs::directory_entry entry(backupRootPath);        //文件入口
        if (entry.status().type() == fs::file_type::directory) {
            for (const auto &iter: fs::directory_iterator(backupRootPath)) {
                if (fs::is_directory(iter.path()) && isValidWorldFolder(iter.path())) {
                    if (currentNum < 10) {
                        builder.textF("%s\n", iter.path().string().c_str());
                        ++currentNum;
                    }
                    ++totalNum;
                }
            }
            if (totalNum > 10) {
                builder.textF("还有其它 %d 个备份未列出", totalNum - 10);
            }
            builder.send(player);
        } else {
            trapdoor::error(player, "无法读取备份目录");
        }
    }
}

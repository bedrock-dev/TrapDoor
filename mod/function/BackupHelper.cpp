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
#include <fstream>
#include "tools/DirtyLogger.h"

namespace mod {

    namespace {
        bool isValidWorldFolder(const std::filesystem::path &path) {
            //check
            return true;
        }

        void writeBackupScript() {
            std::ofstream out("backup.ps1");
            out << R"(
$Date =  $(get-date -f yyyy-MM-dd)+" "+$(get-date -f HH-mm-ss)
$SourcePath = "worlds/Bedrock level"
$Destination = "trapdoor-backup\$Date"
New-Item -Path "trapdoor-backup" -Name "$Date" -ItemType "directory" | Out-Null
Copy-Item -Path $SourcePath -Destination "$Destination" -Recurse | Out-Null
                )";
            out.close();
        }

        std::vector<std::string> getAllBackups(trapdoor::Actor *player) {
            namespace fs = std::filesystem;
            fs::path backupRootPath("trapdoor-backup");
            if (!fs::exists(backupRootPath)) {
                trapdoor::error(player, "备份根目录不存在!");
                return {};
            }
            std::vector<std::string> backupList;
            fs::directory_entry entry(backupRootPath);        //文件入口
            if (entry.status().type() == fs::file_type::directory) {
                for (const auto &iter: fs::directory_iterator(backupRootPath)) {
                    if (fs::is_directory(iter.path()) && isValidWorldFolder(iter.path())) {
                        backupList.push_back(iter.path().string().erase(0, 16));
                    }
                }
            }
            return backupList;
        }

    }


    void backup(trapdoor::Actor *player) {
        trapdoor::broadcastMsg("backup start");
        //我也不知道为啥不会崩服
        trapdoor::bdsMod->getThreadPool()->enqueue([&]() {
            const std::string backupScript = R"(powershell ./backup.ps1)";
            writeBackupScript();
            int r = system(backupScript.c_str());
            if (r == 0) {
                trapdoor::broadcastMsg("backup finished");
            } else {
                trapdoor::broadcastMsg("backup error with code %d", r);
            }
        });
    }

    void initBackup() {
        L_INFO("create backup folder");
        std::filesystem::create_directory("trapdoor-backup");
        //往当前目录写入backup.ps1
    }

    void listAllBackups(trapdoor::Actor *player) {
        auto backupList = getAllBackups(player);
        if (backupList.empty()) {
            trapdoor::error(player, "没有任何备份文件");
            return;
        }
        trapdoor::MessageBuilder builder;
        int totalSize = backupList.size();
        int maxNum = totalSize < 10 ? totalSize : 10;
        for (int i = 0; i < maxNum; i++) {
            builder.num(i).textF(" %s\n", backupList[totalSize - i - 1].c_str());
        }
        if (totalSize > 10) {
            builder.textF("还有 %d 个备份未被列出", totalSize - 10);
        }
        builder.send(player);
    }

    void restore(trapdoor::Actor *player, int index) {
        namespace fs = std::filesystem;
        auto backupList = getAllBackups(player);
        if (index < 0 || index >= backupList.size() || backupList.empty()) {
            trapdoor::error(player, "该备份不存在");
        } else {
            trapdoor::info(player, "正在恢复备份: %s", backupList[backupList.size() - 1 - index].c_str());
        }
    }

}

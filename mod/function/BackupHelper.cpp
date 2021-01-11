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
        const std::string backupScript = R"(powershell ./backup.ps1)";
        trapdoor::broadcastMsg("backup start");
        int r = system(backupScript.c_str());
        trapdoor::broadcastMsg("backup finish with return value %d", r);
    }

    void initBackup() {
        std::filesystem::create_directory("trapdoor-backup");
        //往当前目录写入backup.ps1
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
                        auto backup = iter.path().string().erase(0, 16);
                        builder.num(currentNum).textF("   %s\n", backup.c_str());
                        ++currentNum;
                    }
                    ++totalNum;
                }
            }
            if (totalNum == 0) {
                builder.text("没有发现任何备份");
            }
            if (totalNum > 10) {
                builder.textF("还有其它 %d 个备份未列出", totalNum - 10);
            }
            builder.send(player);
        } else {
            trapdoor::error(player, "无法读取备份目录");
        }
    }

    void restore(trapdoor::Actor *player, int index) {
        namespace fs = std::filesystem;
        fs::path backupRootPath("trapdoor-backup");
        if (!fs::exists(backupRootPath)) {
            trapdoor::error(player, "备份根目录不存在!");
            return;
        }
        int currentNum = 0;
        fs::directory_entry entry(backupRootPath);        //文件入口
        if (entry.status().type() == fs::file_type::directory) {
            for (const auto &iter: fs::directory_iterator(backupRootPath)) {
                if (fs::is_directory(iter.path()) && isValidWorldFolder(iter.path())) {
                    if (currentNum == index) {
                        trapdoor::info(player, "正在恢复备份 %s", iter.path().string().erase(0, 16).c_str());
                        return;
                    }
                    ++currentNum;
                }
            }
            trapdoor::warning(player, "找不到该备份");
        } else {
            trapdoor::error(player, "无法读取备份目录");
        }
    }
}

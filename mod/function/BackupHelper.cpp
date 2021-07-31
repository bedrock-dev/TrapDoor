//
// Created by xhy on 2021/1/9.
//

#include "BackupHelper.h"
#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "language/I18nManager.h"
#include "tick/SimpleProfiler.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include <MsgBuilder.h>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace mod {

namespace {
bool isValidWorldFolder(const std::filesystem::path &path) {
    // check
    return true;
}

void writeBackupScript() {
    std::ofstream out("backup.ps1");
    auto levelName =
        trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()->getLevelName();
    std::string backupScript = trapdoor::format(R"(
$Date =  $(get-date -f yyyy-MM-dd)+" "+$(get-date -f HH-mm-ss)
$SourcePath = "worlds/%s"
$Destination = "trapdoor-backup\$Date"
New-Item -Path "trapdoor-backup" -Name "$Date" -ItemType "directory" | Out-Null
Copy-Item -Path $SourcePath -Destination "$Destination" -Recurse | Out-Null
                )",
                                                levelName.c_str());
    out << backupScript;
    out.close();
}

std::vector<std::string> getAllBackups(trapdoor::Actor *player) {
    namespace fs = std::filesystem;
    fs::path backupRootPath("trapdoor-backup");
    if (!fs::exists(backupRootPath)) {
        trapdoor::error(player, trapdoor::LANG("backup.error.dictNotExist"));
        return {};
    }
    std::vector<std::string> backupList;
    fs::directory_entry entry(backupRootPath); //文件入口
    if (entry.status().type() == fs::file_type::directory) {
        for (const auto &iter : fs::directory_iterator(backupRootPath)) {
            if (fs::is_directory(iter.path()) &&
                isValidWorldFolder(iter.path())) { // NOLINT
                backupList.push_back(iter.path().string().erase(0, 16));
            }
        }
    }
    return backupList;
}

} // namespace

void backup(trapdoor::Actor *player) {
    trapdoor::broadcastMsg(LANG("backup.info.start"));
    //我也不知道为啥不会崩服
    trapdoor::bdsMod->getThreadPool()->enqueue([&]() {
        const std::string backupScript = R"(powershell ./backup.ps1)";
        writeBackupScript();
        int r = system(backupScript.c_str());
        if (r == 0) {
            trapdoor::broadcastMsg(LANG("backup.info.end"));
        } else {
            trapdoor::broadcastMsg(LANG("backup.error.failure"), r);
        }
    });
}

void initBackup() {
    L_DEBUG("create backup folder");
    std::filesystem::create_directory("trapdoor-backup");
    //往当前目录写入backup.ps1
}

void listAllBackups(trapdoor::Actor *player) {
    auto backupList = getAllBackups(player);
    if (backupList.empty()) {
        trapdoor::error(player, LANG("backup.info.noBackups"));
        return;
    }
    trapdoor::MessageBuilder builder;
    int totalSize = backupList.size();
    int maxNum = totalSize < 10 ? totalSize : 10;
    std::string stringBuilder;
    for (int i = 0; i < maxNum; i++) {

        builder.num(i).textF(" %s\n", backupList[totalSize - i - 1].c_str());
        stringBuilder +=
            trapdoor::format(C_INT "\n", backupList[totalSize - i - 1].c_str());
    }
    if (totalSize > 10) {
        builder.textF(LANG("backup.info.moreBackups"), totalSize - 10);
    }
    builder.send(player);
}

void restore(trapdoor::Actor *player, int index) {
    trapdoor::warning(player, "咕咕咕");
    //        return;
    //        namespace fs = std::filesystem;
    //        auto backupList = getAllBackups(player);
    //        if (index < 0 || index >= backupList.size() || backupList.empty())
    //        {
    //            trapdoor::error(player, "该备份不存在");
    //        } else {
    //            trapdoor::info(player, "正在恢复备份: %s",
    //            backupList[backupList.size() - 1 - index].c_str());
    //        }
}

void registerBackupCommand(CommandManager &commandManager) {
    commandManager.registerCmd("backup", "command.backup.desc")
        ->then(
            ARG("b", "command.backup.b.desc", NONE, { mod::backup(player); }))
        ->then(ARG("l", "command.backup.l.desc", NONE,
                   { mod::listAllBackups(player); }))
        ->then(ARG("r", "command.backup.r.desc", INT,
                   { mod::restore(player, holder->getInt()); }));
}

} // namespace mod

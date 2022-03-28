//
// Created by xhy on 2021/1/9.
//

#include "BackupHelper.h"

#include <MsgBuilder.h>

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "language/I18nManager.h"
#include "tick/SimpleProfiler.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"

namespace mod {

    namespace {

        bool isValidWorldFolder(const std::filesystem::path &path) {
            // TODO check if is a valid mineraft bedrock level
            return true;
        }

        void writeBackupScript() {
            L_DEBUG("begin write backup script");
            std::ofstream out("./plugins/trapdoor/backup.ps1");
            auto levelName = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>()
                                 ->getLevelName();
            std::string backupScript = trapdoor::format(R"(
$Date =  $(get-date -f yyyy-MM-dd)+" "+$(get-date -f HH-mm-ss)
$SourcePath = "worlds/%s"
$Destination = "plugins\trapdoor\backup\$Date"
New-Item -Path "plugins\trapdoor\backup" -Name "$Date" -ItemType "directory" | Out-Null
Copy-Item -Path $SourcePath -Destination "$Destination" -Recurse | Out-Null
                )",
                                                        levelName.c_str());
            out << backupScript;
            out.close();
        }

        std::vector<std::string> getAllBackups() {
            namespace fs = std::filesystem;
            fs::path backupRootPath("./plugins/trapdoor/backup");
            if (!fs::exists(backupRootPath)) {
                return {};
            }
            std::vector<std::string> backupList;
            fs::directory_entry entry(backupRootPath);  //文件入口
            if (entry.status().type() == fs::file_type::directory) {
                for (const auto &iter :
                     fs::directory_iterator(backupRootPath)) {
                    if (fs::is_directory(iter.path()) &&
                        isValidWorldFolder(iter.path())) {
                        auto str = iter.path().string();
                        auto p1 = str.rfind('\\');
                        backupList.push_back(
                            str.substr(p1 + 1, str.size() - p1));
                    }
                }
            }
            return backupList;
        }

        void makeBackup(trapdoor::Actor *player) {
            trapdoor::broadcastMsg(LANG("backup.info.start"));
            //我也不知道为啥不会崩服
            trapdoor::bdsMod->getThreadPool()->enqueue([&]() {
                const std::string backupScript =
                    R"(powershell ./plugins/trapdoor/backup.ps1)";
                writeBackupScript();
                int r = system(backupScript.c_str());
                if (r == 0) {
                    trapdoor::broadcastMsg(LANG("backup.info.end"));
                } else {
                    trapdoor::broadcastMsg(LANG("backup.error.failure"), r);
                }
            });
        }

        void listAllBackups(trapdoor::Actor *player, int limit) {
            auto backupList = getAllBackups();
            if (backupList.empty()) {
                trapdoor::error(player, LANG("backup.info.noBackups"));
                return;
            }
            trapdoor::MessageBuilder builder;
            int totalSize = backupList.size();
            int maxNum = totalSize < limit ? totalSize : limit;
            for (int i = 0; i < maxNum; i++) {
                builder.num(i).textF(" %s\n",
                                     backupList[totalSize - i - 1].c_str());
            }
            if (totalSize > 10) {
                builder.textF(LANG("backup.info.moreBackups"), totalSize - 10);
            }
            builder.send(player);
        }

        void restore(trapdoor::Actor *player, int index) {
            trapdoor::warning(player, "咕咕咕");
        }

        void removeBackup(trapdoor::Actor *player, int index) {
            namespace fs = std::filesystem;
            auto backups = getAllBackups();
            auto totalSize = backups.size();
            auto target_backup_to_remove = backups[totalSize - index - 1];
            auto remove_path =
                "./plugins/trapdoor/backup/" + target_backup_to_remove;
            // TODO: add remove to thread pool.
            trapdoor::info(player, "Remove path is [%s]", remove_path.c_str());
            std::error_code ec;
            fs::remove_all(remove_path, ec);
            L_DEBUG("INfo is %s", ec.message().c_str());
        }
    }  // namespace

    void initBackup() {
        L_DEBUG("create backup folder");
        namespace fs = std::filesystem;
        std::filesystem::create_directory("./plugins/trapdoor/backup");
        //往当前目录写入backup.ps1
    }

    void registerBackupCommand(CommandManager &commandManager) {
        commandManager.registerCmd("backup", "command.backup.desc")
            ->then(ARG("b", "command.backup.b.desc", NONE,
                       { mod::makeBackup(player); }))
            ->then(ARG("l", "command.backup.l.desc", NONE,
                       { mod::listAllBackups(player, 1000); }))
            ->then(ARG("r", "command.backup.r.desc", INT,
                       { mod::restore(player, holder->getInt()); }))
            ->then(ARG("del", "command.backup.r.desc", INT,
                       { mod::removeBackup(player, holder->getInt()); }))
            ->then(ARG("crash", "command.backup.crash.desc", NONE, {
                //这种指令的存在真的好吗
                // trapdoor::warning(player, "this command has been removed");
                *((char *)(0)) = 0;
            }));
    }

}  // namespace mod

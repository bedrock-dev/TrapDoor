//
// Created by xhy on 2021/1/6.
//

#include "PlayerStatisticManager.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"

namespace mod {
    int mod::PlayerStatisticManager::createPlayerActionTable() {
        const std::string playerActionTableSQL =
                R"(
            create table if not exists player_acton(
            action_id integer primary key autoincrement,
            player_id VARCHAR(128) not null,
            action_time timestamp not null default (datetime('now','localtime')),
            action_type int,
            action_dim int,
            action_p_x int,
            action_p_y int,
            action_p_z int,
            action_string VARCHAR(512)
            )
            )";
        return this->executeSQL(playerActionTableSQL);
    }

    int PlayerStatisticManager::executeSQL(const std::string &sql) {
        char *errorMsg;
        auto rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMsg);
        if (rc != SQLITE_OK) {
            L_DEBUG("SQL error: %s\n", errorMsg);
            sqlite3_free(errorMsg);
        }
        return rc;
    }

    void PlayerStatisticManager::insetPlayerAction(const std::string &playerName, const trapdoor::BlockPos &pos,
                                                   PlayerStatisticManager::PLAYER_ACTION playerAction, int dim,
                                                   const std::string &msg) {

        auto sql = trapdoor::format(
                "insert into player_acton(player_id,action_type,action_dim,action_p_x,action_p_y,action_p_z,action_string)\n"
                "        VALUES ('%s', %d,%d,%d,%d,%d, '%s')",
                playerName.c_str(), playerAction, dim, pos.x, pos.y, pos.z, msg.c_str()
        );
        this->executeSQL(sql);
    }

    void PlayerStatisticManager::init(const std::string &dbName) {
        L_DEBUG("begin init player statistic database");
        sqlite3_open(dbName.c_str(), &this->db);
        if (this->createPlayerActionTable() != 0) {
            L_ERROR("create table failure");
        } else {
            L_DEBUG("success create table");
        }
    }
}

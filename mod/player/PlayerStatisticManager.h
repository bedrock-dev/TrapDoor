//
// Created by xhy on 2021/1/6.
//

#ifndef MOD_PLAYERSTATISTICMANAGER_H
#define MOD_PLAYERSTATISTICMANAGER_H

#include "lib/sqlite3.h"
#include <string>
#include "graphics/BlockPos.h"
#include "tools/noncopyable .h"

namespace mod {

//    class PlayerStatisticManager : noncopyable {
//        sqlite3 *db = nullptr;
//        bool enable = false;
//
//        int executeSQL(const std::string &sql);
//
//        int createPlayerActionTable();
//
//    public:
//        enum PLAYER_ACTION {
//            DESTROY_BLOCK,
//            PLACE_BLOCK
//        };
//
//        inline void setAble(bool able) { this->enable = able; }
//
//        inline bool isEnable() const { return this->enable; }
//
//        void init(const std::string &dbName);
//
//        void insetPlayerAction(const std::string &playerName, const trapdoor::BlockPos &pos,
//                               PLAYER_ACTION playerAction, int dim, const std::string &msg
//        );
//    };
}


#endif //MOD_PLAYERSTATISTICMANAGER_H

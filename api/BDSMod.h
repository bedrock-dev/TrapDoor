//
// Created by xhy on 2020/8/25.
//
/*
 *
 *
 */
#ifndef TRAPDOOR_TRAPDOOR_H
#define TRAPDOOR_TRAPDOOR_H

#include <set>
#include <cstdio>
#include <map>
#include <string>
#include "commands/CommandManager.h"
#include "world/Level.h"

typedef size_t Tick;
namespace trapdoor {
    class BDSMod {
    protected:
        typedef void CommandRegistry;
        Level *serverLevel{};
        CommandRegistry *commandRegistry{};
        CommandManager commandManager;
    public:
        Level *getLevel();

        void setLevel(Level *level);

        CommandRegistry *getCommandRegistry();

        void setCommandRegistry(CommandRegistry *registry);

        CommandManager &getCommandManager();

        virtual void registerCommands();

        template<typename Mod>
        Mod *asInstance() {
            return reinterpret_cast<Mod *>(this);
        }
    };

    void initializeMod(BDSMod *bdsMod);

    extern BDSMod *bdsMod;
}

#endif //TRAPDOOR_TRAPDOOR_H

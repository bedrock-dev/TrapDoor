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
#include "PlayerBuffer.h"
#include "tools/ThreadPool.h"
#include "tools/noncopyable .h"

namespace trapdoor {


    class BDSMod : public noncopyable {
    public:
        struct ModConfig {
            size_t particleViewDistance = 256;
            bool particlePerformanceMode = false;
        };
    protected:
        typedef void CommandRegistry;
        Level *serverLevel{};
        CommandRegistry *commandRegistry{};
        CommandManager commandManager;
        std::map<std::string, PlayerBuffer> playerCache;
        ThreadPool *threadPool = nullptr;
        ModConfig config;
        BlockPalette *palette;
    public:

        Level *getLevel();

        inline BlockPalette *getPalette() { return this->palette; }

        void setLevel(Level *level);

        inline void setBlockPalette(BlockPalette *p) { this->palette = p; }

        CommandRegistry *getCommandRegistry();

        void setCommandRegistry(CommandRegistry *registry);

        virtual void initialize();

        CommandManager &getCommandManager();

        inline ThreadPool *getThreadPool() { return this->threadPool; }

        virtual void registerCommands();


        virtual void useOnHook(Actor *player, const std::string &itemName, BlockPos &pos,
                               unsigned int facing,
                               const Vec3 &) = 0;

        virtual bool attackEntityHook(Actor *player, Actor *entity) = 0;

        virtual CommandPermissionLevel
        resetVanillaCommandLevel(const std::string &name, CommandPermissionLevel oldLevel) { return oldLevel; }

        std::map<std::string, PlayerBuffer> &getPlayerBuffer();

        template<typename Mod>
        Mod *asInstance() {
            return reinterpret_cast<Mod *>(this);
        }

        ModConfig &getCfg() { return this->config; }


    public:
        trapdoor::Actor *fetchEntity(int64_t id, bool b);
    };

    void initializeMod(BDSMod *bdsMod);

    extern BDSMod *bdsMod;
}

#endif //TRAPDOOR_TRAPDOOR_H

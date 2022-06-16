//
// Created by xhy on 2020/8/25.
//
/*
 *
 *
 */
#ifndef TRAPDOOR_TRAPDOOR_H
#define TRAPDOOR_TRAPDOOR_H

#include <cstdio>
#include <map>
#include <set>
#include <string>

#include "PlayerBuffer.h"
#include "commands/CommandManager.h"
#include "language/I18nManager.h"
#include "tools/ThreadPool.h"
#include "tools/noncopyable .h"
#include "world/Level.h"

namespace trapdoor {

    class BDSMod : public noncopyable {
       public:
        struct ModConfig {
            size_t particleViewDistance = 96;
            bool particlePerformanceMode = false;
        };

        void registerLangCommand();

       protected:
        typedef void CommandRegistry;
        Level *serverLevel{};
        CommandRegistry *commandRegistry{};
        CommandManager commandManager;
        std::map<std::string, PlayerBuffer> playerCache;
        ThreadPool *threadPool = nullptr;
        ModConfig config;
        //  I18nManager i18NManager;
        size_t trapdoorTick = 0;

       public:
        void tick();

        inline size_t getTrapdoorTick() { return this->trapdoorTick; }

        Level *getLevel();

        void setLevel(Level *level);

        CommandRegistry *getCommandRegistry();

        void setCommandRegistry(CommandRegistry *registry);

        virtual void initialize();

        CommandManager &getCommandManager();

        inline ThreadPool *getThreadPool() { return this->threadPool; }

        virtual void registerCommands();

        virtual void useOnHook(Actor *player, const std::string &itemName,
                               BlockPos &pos, unsigned int facing,
                               const Vec3 &) = 0;

        virtual bool attackEntityHook(Actor *player, Actor *entity) = 0;

        virtual CommandPermissionLevel resetVanillaCommandLevel(
            const std::string &name, CommandPermissionLevel oldLevel) {
            return oldLevel;
        }

        std::map<std::string, PlayerBuffer> &getPlayerBuffer();

        template <typename Mod>
        Mod *asInstance() {
            return reinterpret_cast<Mod *>(this);
        }

        ModConfig &getCfg() { return this->config; }

       public:
        trapdoor::Actor *fetchEntity(int64_t id, bool b);

        //  inline I18nManager &getI18NManager() { return this->i18NManager; }
    };

    void initializeMod(BDSMod *bdsMod);

    extern BDSMod *bdsMod;
}  // namespace trapdoor

#endif  // TRAPDOOR_TRAPDOOR_H

//
// Created by xhy on 2021/2/16.
//

#include "TrapdoorTest.h"

#define COMMAND_TEST(TEST_NAME)                                     \
    void commandTest_##TEST_NAME(trapdoor::CommandManager &manager, \
                                 trapdoor::Actor *player)
#define TEST(TEST_NAME) commandTest_##TEST_NAME(manager, player);
#define RUN_CMD(cmd)                                 \
    {                                                \
        trapdoor::info(player, "TEST: [" cmd "]\n"); \
        manager.parse(player, cmd);                  \
    }
namespace mod::test {
    namespace {
        std::map<std::string, bool> &getNeedMoreTestItems() {
            static std::map<std::string, bool> testItems;
            return testItems;
        }

        void printTestStatus(trapdoor::Actor *actor) {
            const auto &items = getNeedMoreTestItems();
            std::string stringBuilder;
            for (const auto &i : items) {
                if (i.second) {
                    stringBuilder += trapdoor::format(
                        "- %s  " C_GREEN(% d) "\n", i.first.c_str(), i.second);
                } else {
                    stringBuilder += trapdoor::format(
                        "- %s  " C_RED(% d) "\n", i.first.c_str(), i.second);
                }
            }
            trapdoor::info(actor, stringBuilder);
        }

        void markPassed(const std::string &item, trapdoor::Actor *actor) {
            auto iter = getNeedMoreTestItems().find(item);
            if (iter != getNeedMoreTestItems().end()) {
                getNeedMoreTestItems()[item] = true;
                trapdoor::info(actor, "mark %s passed", item.c_str());
            } else {
                trapdoor::warning(actor, "no items");
            }
        }

        void markUnPassed(const std::string &item, trapdoor::Actor *actor) {
            auto iter = getNeedMoreTestItems().find(item);
            if (iter != getNeedMoreTestItems().end()) {
                getNeedMoreTestItems()[item] = false;
                trapdoor::info(actor, "mark %s unPassed", item.c_str());
            } else {
                trapdoor::warning(actor, "no items");
            }
        }

        void addManualTestItem(const std::string &s) {
            getNeedMoreTestItems()[s] = false;
        }

        void buildTestPlatform(trapdoor::Actor *player) {
            // build space
            auto *bs = player->getBlockSource();
            for (int i = -16; i < 16; i++) {
                for (int j = -16; j < 16; j++) {
                    for (int k = -1; k < 30; k++) {
                        trapdoor::BlockPos pos = player->getStandPosition() +
                                                 trapdoor::BlockPos(i, k, j);
                        bs->setBlock(&pos, getBlockByID(AIR));
                    }
                }
            }
            // hopper test
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    trapdoor::BlockPos pos =
                        player->getStandPosition() +
                        trapdoor::BlockPos(2 * i - 16, 2, 2 * j - 16);
                    trapdoor::Block *b =
                        getBlockByID(CONCRETE, (unsigned short)(i * 4 + j));
                    bs->setBlock(&pos, b);
                    auto hopperV = rand() % 6;
                    auto pos2 = pos + trapdoor::BlockPos(0, 1, 0);
                    auto *b2 = getBlockByID(HOPPER, (unsigned short)hopperV);
                    bs->setBlock(&pos2, b2);
                    auto *wool = getBlockByID(WOOL, hopperV == 0 ? 0 : 4);
                    auto pos3 = pos + trapdoor::BlockPos(0, -1, 0);
                    bs->setBlock(&pos3, b2);
                }
            }

            // village test
            auto bedPos = player->getStandPosition();
            player->getBlockSource()->setBlock(&bedPos, getBlockByID(BED));
            trapdoor::CommandManager::runVanillaCommand(
                "execute @p ~ ~ ~ summon ~ ~2 ~ villager");

            // rotate
            trapdoor::CommandManager::runVanillaCommand(
                "give " + player->getNameTag() + " cactus");
            std::vector<trapdoor::BlockType> blocks = {PISTON,
                                                       STICKY_PISTON,
                                                       DISPENSER,
                                                       REDSTONE_TORCH,
                                                       CHEST,
                                                       OBSERVER,
                                                       WOODEN_SLAB,
                                                       ACACIA_STAIRS,
                                                       BARREL,
                                                       ACACIA_BUTTON,
                                                       DROPPER,
                                                       POWERED_REPEATER,
                                                       UNPOWERED_REPEATER,
                                                       POWERED_COMPARATOR,
                                                       POWERED_REPEATER};
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    auto index = i * 4 + j;
                    if (index < blocks.size()) {
                        trapdoor::BlockPos p =
                            player->getStandPosition() +
                            trapdoor::BlockPos(i + 2, 0, j + 2);
                        bs->setBlock(&p, getBlockByID(blocks[index]));
                    }
                }
            }

            // redstone signal
            trapdoor::CommandManager::runVanillaCommand(
                "give " + player->getNameTag() + " stick");
        }
    }  // namespace

    COMMAND_TEST(apicfg){
        RUN_CMD("/apicfg") RUN_CMD("/apicfg ?") RUN_CMD("/apicfg pm 1")
            RUN_CMD("/apicfg pm 0") RUN_CMD("/apicfg pvd 1")
                RUN_CMD("/apicfg pvd 12") RUN_CMD("/apicfg pvd -12")}

    COMMAND_TEST(td){RUN_CMD("/td?")}

    COMMAND_TEST(func){
        RUN_CMD("/func") RUN_CMD("/func ?") RUN_CMD("/func hopper 1")
            RUN_CMD("/func hopper 0") RUN_CMD("/func spawn true")
                RUN_CMD("/func spawn false") RUN_CMD("/func rotate 1")
                    RUN_CMD("/func rotate 0") RUN_CMD("/func ncud 1")
                        RUN_CMD("/func ncud 0") RUN_CMD("/func expl true")
                            RUN_CMD("/func expl false")}

    COMMAND_TEST(lang){RUN_CMD("/lang") RUN_CMD("/lang list")
                           RUN_CMD("/lang set zh_cn")}

    COMMAND_TEST(tick){
        RUN_CMD("/tick") RUN_CMD("/tick ?") RUN_CMD("/tick fz")
            RUN_CMD("/tick fw 20") RUN_CMD("/tick fw 601") RUN_CMD("/tick r")
                RUN_CMD("/tick acc 30") RUN_CMD("/tick acc -1")
                    RUN_CMD("/tick acc 3") RUN_CMD("/tick r")
                        RUN_CMD("/tick slow 67") RUN_CMD("/tick slow 1")
                            RUN_CMD("/tick slow 4") RUN_CMD("/tick r")}

    COMMAND_TEST(counter){RUN_CMD("/counter") RUN_CMD("/counter p 15")
                              RUN_CMD("/counter p -1") RUN_CMD("/counter p 16")
                                  RUN_CMD("/counter p 7")
                                      RUN_CMD("/counter r 7")}

    COMMAND_TEST(os){RUN_CMD("/os")}

    COMMAND_TEST(self) {
        RUN_CMD("/self")
        RUN_CMD("/self rs 1")
        RUN_CMD("/self rs 0")
        RUN_CMD("/self me true")
        RUN_CMD("/self me false")
        RUN_CMD("/self chunk true")
        RUN_CMD("/self chunk 0");
    }

    COMMAND_TEST(gameMode){RUN_CMD("/o") RUN_CMD("/s") RUN_CMD("/c")}

    COMMAND_TEST(list){RUN_CMD("/l") RUN_CMD("/here")}

    COMMAND_TEST(village){
        RUN_CMD("/village") RUN_CMD("/village list") RUN_CMD("/village b true")
            RUN_CMD("/village b false") RUN_CMD("/village s 1")
                RUN_CMD("/village s 0") RUN_CMD("/village p true")
                    RUN_CMD("/village p false") RUN_CMD("/village v true")
                        RUN_CMD("/village v false") RUN_CMD("/village n")}

    COMMAND_TEST(hsa){RUN_CMD("/hsa") RUN_CMD("/hsa show 1")
                          RUN_CMD("/hsa show false") RUN_CMD("/hsa clear")
                              RUN_CMD("/hsa draw") RUN_CMD("/hsa list")}

    COMMAND_TEST(draw){RUN_CMD("/func") RUN_CMD("/func draw false")
                           RUN_CMD("/func draw 1") RUN_CMD("/draw sp 2")
                               RUN_CMD("/draw sp -3") RUN_CMD("/draw ci 5")
                                   RUN_CMD("/draw ci -10")}

    COMMAND_TEST(cl){RUN_CMD("/cl") RUN_CMD("/cl 12+sin(0.5+2*pi)-log2(12)")
                         RUN_CMD("/cl 1/0") RUN_CMD("/cl log(-1)")}

    COMMAND_TEST(mspt){RUN_CMD("/mspt")}

    COMMAND_TEST(slime) {
        RUN_CMD("/slime")
        RUN_CMD("/slime show 1")
        RUN_CMD("/slime show 0")
        RUN_CMD("/slime c")
        RUN_CMD("/slime r -1")
        RUN_CMD("/slime r 4")
    }

    void testAll(trapdoor::Actor *player, CommandManager &manager) {
        trapdoor::info(player, "begin Test");
        TEST(apicfg)
        TEST(gameMode)
        TEST(func)
        TEST(tick)
        TEST(lang)
        TEST(list)
        TEST(self)
        TEST(os)
        TEST(counter)
        TEST(draw)
        TEST(hsa)
        TEST(village)
        TEST(cl)
        //  TEST(td)
        trapdoor::info(player, "end Test");
    }

    void addManualTest() {
        addManualTestItem("backup");
        addManualTestItem("village");
        addManualTestItem("prof");
        addManualTestItem("spawn");
        addManualTestItem("rotate");
        addManualTestItem("ncud");
        addManualTestItem("chunk");
        addManualTestItem("me");
        addManualTestItem("rs");
        addManualTestItem("counter");
        addManualTestItem("draw");
        addManualTestItem("slime");
        addManualTestItem("hsa");
    }

    void registerTestCommand(CommandManager &manager) {
#ifdef BETA
        addManualTest();
        manager.registerCmd("test")
            ->then(ARG("p", "通过某项测试", STR,
                       { markPassed(holder->getString(), player); }))
            ->then(ARG("u", "通过某项测试", STR,
                       { markUnPassed(holder->getString(), player); }))
            ->then(ARG("l", "列出所有手动测试项", NONE,
                       { printTestStatus(player); }))
            ->then(ARG("b", "手动测试项", STR, { buildTestPlatform(player); }))
            ->execute(
                [&](trapdoor::ArgHolder *holder, trapdoor::Actor *player) {
                    testAll(player, manager);
                });
#endif
    }
}  // namespace mod::test

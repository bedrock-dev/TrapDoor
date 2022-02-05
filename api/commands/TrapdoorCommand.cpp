
#include <Global.h>
#include "TrapdoorCommand.h"

#include "../../LiteLoaderSDK/Header/EventAPI.h"
#include "../../LiteLoaderSDK/Header/RegCommandAPI.h"

using namespace RegisterCommandHelper;
class VillageCommand : public Command {
    enum class Operation {
        Help,
        Bound,
        Center,
        List,
        Nearest,
        POIBound,
        Spawning,
        Test,
        Verbels,
    } mOperation;
    bool mSwitch;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "village", "村庄相关功能", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("VillageAction",
                                    {{"?", Operation::Help},
                                     {"list", Operation::List},
                                     {"n", Operation::Nearest},
                                     {"test", Operation::Test}});
        registry.addEnum<Operation>("VillageActionSwitch",
                                    {{"b", Operation::Bound},
                                     {"c", Operation::Center},
                                     {"p", Operation::POIBound},
                                     {"s", Operation::Spawning},
                                     {"v", Operation::Verbels}});
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &VillageCommand::mOperation, "action", "VillageAction");
        auto actionSwitch = makeMandatory<CommandParameterDataType::ENUM>(
            &VillageCommand::mOperation, "action", "VillageActionSwitch");
        action.addOptions((CommandParameterOption)1);
        actionSwitch.addOptions((CommandParameterOption)1);

        auto switchParam = makeMandatory(&VillageCommand::mSwitch, "activate");

        registry.registerOverload<VillageCommand>("village", action);
        registry.registerOverload<VillageCommand>("village", actionSwitch,
                                                  switchParam);
    };
};
class ApiCfgCommand : public Command {
    enum class Operation {
        Help,
        VisibleDistance,
        PM,
    } mOperation;
    bool mSwitch;
    int mDistance;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "apicfg", "粒子显示效果设置", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("ApiCfgAction", {
                                                        {"?", Operation::Help},
                                                    });
        registry.addEnum<Operation>("ApiCfgActionSwitch",
                                    {
                                        {"pvd", Operation::VisibleDistance},
                                    });
        registry.addEnum<Operation>("ApiCfgActionInt",
                                    {
                                        {"pm", Operation::PM},
                                    });
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &ApiCfgCommand::mOperation, "action", "ApiCfgAction");
        auto actionSwitch = makeMandatory<CommandParameterDataType::ENUM>(
            &ApiCfgCommand::mOperation, "action", "ApiCfgActionSwitch");
        auto actionInt = makeMandatory<CommandParameterDataType::ENUM>(
            &ApiCfgCommand::mOperation, "action", "ApiCfgActionInt");
        action.addOptions((CommandParameterOption)1);
        actionSwitch.addOptions((CommandParameterOption)1);
        actionInt.addOptions((CommandParameterOption)1);

        auto switchParam = makeMandatory(&ApiCfgCommand::mSwitch, "switch");
        auto distanceParam =
            makeMandatory(&ApiCfgCommand::mDistance, "VisibleDistance");

        registry.registerOverload<ApiCfgCommand>("apicfg", action);
        registry.registerOverload<ApiCfgCommand>("apicfg", actionSwitch,
                                                 switchParam);
        registry.registerOverload<ApiCfgCommand>("apicfg", actionInt,
                                                 distanceParam);
    };
};
class TickCommand : public Command {
    enum class Operation {
        Help,
        Frezze,
        Slow,
        Accelerate,
        Forward,
        Reset,
        Qurey,
    } mOperation;
    int mTick;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "tick", "改变世界运行状态", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("TickActionInt",
                                    {
                                        {"acc", Operation::Accelerate},
                                        {"fw", Operation::Forward},
                                        {"slow", Operation::Slow},
                                    });
        registry.addEnum<Operation>("TickAction", {
                                                      {"?", Operation::Help},
                                                      {"fz", Operation::Frezze},
                                                      {"q", Operation::Qurey},
                                                      {"r", Operation::Reset},
                                                  });
        auto actionInt = makeMandatory<CommandParameterDataType::ENUM>(
            &TickCommand::mOperation, "action", "TickActionInt");
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &TickCommand::mOperation, "action", "TickAction");
        actionInt.addOptions((CommandParameterOption)1);
        action.addOptions((CommandParameterOption)1);

        auto tickParam = makeMandatory(&TickCommand::mTick, "radius");

        registry.registerOverload<TickCommand>("tick", actionInt, tickParam);
        registry.registerOverload<TickCommand>("tick", action);
    };
};
class ProfileCommand : public Command {
    enum class Operation {
        Help,
        Actor,
    } mOperation;
    bool mOperation_isSet;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "prof", "游戏性能分析", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("ProfileAction",
                                    {
                                        {"?", Operation::Help},
                                        {"actor", Operation::Actor},
                                    });
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &ProfileCommand::mOperation, "action", "ProfileAction",
            &ProfileCommand::mOperation_isSet);
        action.addOptions((CommandParameterOption)1);

        registry.registerOverload<ProfileCommand>("prof");
        registry.registerOverload<ProfileCommand>("prof", action);
    };
};
class FunctionCommand : public Command {
    enum class Operation {
        Help,
        Draw,
        Explosion,
        Hopper,
        NeighborChanged,
        Rotate,
        Spawn,
    } mOperation;
    bool mSwitch;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "func", "部分全局功能的开关", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("FunctionAction",
                                    {
                                        {"?", Operation::Help},
                                    });
        registry.addEnum<Operation>("FunctionActionSwitch",
                                    {
                                        {"draw", Operation::Draw},
                                        {"expl", Operation::Explosion},
                                        {"hopper", Operation::Hopper},
                                        {"ncud", Operation::NeighborChanged},
                                        {"rotate", Operation::Rotate},
                                        {"spawn", Operation::Spawn},
                                    });
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &FunctionCommand::mOperation, "action", "FunctionAction");
        auto actionSwitch = makeMandatory<CommandParameterDataType::ENUM>(
            &FunctionCommand::mOperation, "action", "FunctionActionSwitch");
        action.addOptions((CommandParameterOption)1);
        actionSwitch.addOptions((CommandParameterOption)1);

        auto switchParam = makeMandatory(&FunctionCommand::mSwitch, "switch");

        registry.registerOverload<FunctionCommand>("func", action);
        registry.registerOverload<FunctionCommand>("func", actionSwitch,
                                                   switchParam);
    };
};
class HSACommand : public Command {
    enum class Operation {
        Help,
        Show,
        Clear,
        Draw,
        Find,
        List,
    } mOperation;
    bool mSwitch;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "hsa", "部分全局功能的开关", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("HSAActionSwitch",
                                    {
                                        {"show", Operation::Show},
                                    });
        registry.addEnum<Operation>("HSAAction",
                                    {
                                        {"?", Operation::Help},
                                        {"clear", Operation::Clear},
                                        {"draw", Operation::Draw},
                                        {"find", Operation::Find},
                                        {"list", Operation::List},
                                    });
        auto actionSwitch = makeMandatory<CommandParameterDataType::ENUM>(
            &HSACommand::mOperation, "action", "HSAActionSwitch");
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &HSACommand::mOperation, "action", "HSAAction");
        actionSwitch.addOptions((CommandParameterOption)1);
        action.addOptions((CommandParameterOption)1);

        auto switchParam = makeMandatory(&HSACommand::mSwitch, "switch");

        registry.registerOverload<HSACommand>("hsa", actionSwitch, switchParam);
        registry.registerOverload<HSACommand>("hsa", action);
    };
};
class SlimeCommand : public Command {
    enum class Operation {
        Help,
        Show,
        Clear,
        Radius,
    } mOperation;
    bool mSwitch;
    int mRadius;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "slime", "部分全局功能的开关", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("SlimeActionSwitch",
                                    {
                                        {"show", Operation::Show},
                                    });
        registry.addEnum<Operation>("SlimeActionInt",
                                    {
                                        {"r", Operation::Radius},
                                    });
        registry.addEnum<Operation>("SlimeAction", {
                                                       {"?", Operation::Help},
                                                       {"c", Operation::Clear},
                                                   });
        auto actionSwitch = makeMandatory<CommandParameterDataType::ENUM>(
            &SlimeCommand::mOperation, "action", "SlimeActionSwitch");
        auto actionInt = makeMandatory<CommandParameterDataType::ENUM>(
            &SlimeCommand::mOperation, "action", "SlimeActionInt");
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &SlimeCommand::mOperation, "action", "SlimeAction");
        actionSwitch.addOptions((CommandParameterOption)1);
        actionInt.addOptions((CommandParameterOption)1);
        action.addOptions((CommandParameterOption)1);

        auto switchParam = makeMandatory(&SlimeCommand::mSwitch, "switch");
        auto radiusParam = makeMandatory(&SlimeCommand::mRadius, "radius");

        registry.registerOverload<SlimeCommand>("slime", actionSwitch,
                                                switchParam);
        registry.registerOverload<SlimeCommand>("slime", actionInt,
                                                radiusParam);
        registry.registerOverload<SlimeCommand>("slime", action);
    };
};
class SelfCommand : public Command {
    enum class Operation {
        Help,
        Chunk,
        Measuring,
        RedstoneSource,
    } mOperation;
    bool mSwitch;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "slime", "部分全局功能的开关", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("SelfAction", {
                                                      {"?", Operation::Help},
                                                  });
        registry.addEnum<Operation>("SelfActionSwitch",
                                    {
                                        {"chunk", Operation::Chunk},
                                        {"me", Operation::Measuring},
                                        {"rs", Operation::RedstoneSource},
                                    });
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &SelfCommand::mOperation, "action", "SelfAction");
        auto actionSwitch = makeMandatory<CommandParameterDataType::ENUM>(
            &SelfCommand::mOperation, "action", "SelfActionSwitch");
        action.addOptions((CommandParameterOption)1);
        actionSwitch.addOptions((CommandParameterOption)1);

        auto switchParam = makeMandatory(&SelfCommand::mSwitch, "switch");

        registry.registerOverload<SelfCommand>("slime", action);
        registry.registerOverload<SelfCommand>("slime", actionSwitch,
                                               switchParam);
    };
};
class DrawCommand : public Command {
    enum class Operation {
        Help,
        Chunk,
        Circle,
        MaxRadius,
        Sphere,
    } mOperation;
    int mRadius;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "draw", "简单建造", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("DrawAction", {
                                                      {"?", Operation::Help},
                                                      {"ch", Operation::Chunk},
                                                  });
        registry.addEnum<Operation>("DrawActionInt",
                                    {
                                        {"ci", Operation::Circle},
                                        {"ci", Operation::Circle},
                                        {"mr", Operation::MaxRadius},
                                        {"sp", Operation::Sphere},
                                    });
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &DrawCommand::mOperation, "action", "DrawAction");
        auto actionInt = makeMandatory<CommandParameterDataType::ENUM>(
            &DrawCommand::mOperation, "action", "DrawActionInt");
        action.addOptions((CommandParameterOption)1);
        actionInt.addOptions((CommandParameterOption)1);

        auto radiusParam = makeMandatory(&DrawCommand::mRadius, "radius");

        registry.registerOverload<DrawCommand>("draw", action);
        registry.registerOverload<DrawCommand>("draw", action, radiusParam);
    };
};
class CounterCommand : public Command {
    enum class Operation {
        Help,
        Print,
        Reset,
    } mOperation;
    bool mSwitch;
    int mDistance;
    virtual void execute(class CommandOrigin const& origin,
                         class CommandOutput& output) const override {
        output.error("Please install trapdoor");
    };

   public:
    static void setup(CommandRegistry& registry) {
        registry.registerCommand(
            "counter", "漏斗计数器", CommandPermissionLevel::Any,
            {(CommandFlagValue)0}, {(CommandFlagValue)0x80});
        registry.addEnum<Operation>("CounterAction", {
                                                         {"?", Operation::Help},
                                                     });
        registry.addEnum<Operation>("CounterActionInt",
                                    {
                                        {"p", Operation::Print},
                                        {"r", Operation::Reset},
                                    });
        auto action = makeMandatory<CommandParameterDataType::ENUM>(
            &CounterCommand::mOperation, "action", "CounterAction");
        auto actionInt = makeMandatory<CommandParameterDataType::ENUM>(
            &CounterCommand::mOperation, "action", "CounterActionInt");
        action.addOptions((CommandParameterOption)1);
        actionInt.addOptions((CommandParameterOption)1);

        auto channelParam =
            makeMandatory(&CounterCommand::mDistance, "Channel");

        registry.registerOverload<CounterCommand>("counter", action);
        registry.registerOverload<CounterCommand>("counter", actionInt,
                                                  channelParam);
    };
};

void registryCommand() {
    Event::RegCmdEvent::subscribe([](Event::RegCmdEvent ev) {
        VillageCommand::setup(*ev.mCommandRegistry);
        ApiCfgCommand::setup(*ev.mCommandRegistry);
        TickCommand::setup(*ev.mCommandRegistry);
        ProfileCommand::setup(*ev.mCommandRegistry);
        FunctionCommand::setup(*ev.mCommandRegistry);
        HSACommand::setup(*ev.mCommandRegistry);
        SlimeCommand::setup(*ev.mCommandRegistry);
        SelfCommand::setup(*ev.mCommandRegistry);
        DrawCommand::setup(*ev.mCommandRegistry);
        CounterCommand::setup(*ev.mCommandRegistry);
        return true;
    });
}

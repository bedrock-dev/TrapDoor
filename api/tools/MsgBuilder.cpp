//
// Created by xhy on 2020/8/25.
//
//todo 这个builder要重写，因为不够实用，尽量用模板重新实现一个类printf接口的Buider
#include "MsgBuilder.h"
#include "Message.h"
#include "entity/Actor.h"

namespace trapdoor {
    const uint8_t MessageBuilder::BLACK = 0x0;
    const uint8_t MessageBuilder::DARK_READ = 0x4;
    const uint8_t MessageBuilder::GOLD = 0x6;
    const uint8_t MessageBuilder::GRAY = 0x7;
    const uint8_t MessageBuilder::BLUE = 0x9;
    const uint8_t MessageBuilder::GREEN = 0xa;
    const uint8_t MessageBuilder::AQUA = 0xb;
    const uint8_t MessageBuilder::RED = 0xc;
    const uint8_t MessageBuilder::LIGHT_PURPLE = 0xd;
    const uint8_t MessageBuilder::YELLOW = 0xe;
    const uint8_t MessageBuilder::WHITE = 0xf;

    const uint8_t MessageBuilder::BOLD = 0x10;
    const uint8_t MessageBuilder::ITALIC = 0x20;
    const uint8_t MessageBuilder::RESET = 0x30;

    const std::map<uint8_t, std::string> MessageBuilder::STYLE_MAP = {
            {BLACK,        "§0"},
            {DARK_READ,    "§4"},
            {GOLD,         "§6"},
            {GRAY,         "§7"},
            {BLUE,         "§9"},
            {GREEN,        "§a"},
            {AQUA,         "§b"},
            {RED,          "§c"},
            {LIGHT_PURPLE, "§d"},
            {YELLOW,       "§e"},
            {WHITE,        "§f"},
            {BOLD,         "§l"},
            {ITALIC,       "§o"},
            {RESET,        "§r"}
    };

    MessageBuilder &MessageBuilder::text(const std::string &s) {
        messageBuffer.emplace_back(s);
        return *this;
    }

    MessageBuilder &MessageBuilder::pos(const BlockPos &pos) {
        return this->sText(pos.toString(), AQUA | BOLD);
    }

    MessageBuilder &MessageBuilder::vec3(const Vec3 &vec3) {
        return this->sText(vec3.toString(), AQUA | BOLD);
    }

    MessageBuilder &MessageBuilder::aabb(AABB aabb) {
        auto str = "[" + aabb.p1.toString() + "," + aabb.p2.toString() + "]";
        return this->sText(str, BLUE);
    }

    std::string MessageBuilder::get() {
        std::string s;
        for (const auto &i:messageBuffer) {
            s.append(i);
        }
        return s;
    }


    MessageBuilder &MessageBuilder::sText(const std::string &s, uint8_t style) {
        auto fontColor = style & 0x0fu;
        auto fontStyle = style & 0xf0u;
        auto iter = STYLE_MAP.find(fontColor);
        if (iter != STYLE_MAP.end())
            messageBuffer.push_back(iter->second);
        iter = STYLE_MAP.find(fontStyle);
        if (iter != STYLE_MAP.end() && fontStyle != 0x0)
            messageBuffer.push_back(iter->second);
        messageBuffer.push_back(s);
        messageBuffer.push_back(STYLE_MAP.at(RESET));
        return *this;
    }

    void MessageBuilder::send(Actor *actor) {
        info(actor, get());
        //todo: rewrite
        // info(get());
    }

    void MessageBuilder::broadcast() {
        broadcastMsg(this->get());
    }
}

